#include "fpmas.h"
#include "agents.h"

using fpmas::synchro::GhostMode;
using fpmas::synchro::HardSyncMode;
using fpmas::model::Behavior;

#ifndef SYNC_MODE
#define SYNC_MODE HardSyncMode
#endif

FPMAS_JSON_SET_UP(AGENT_TYPES);

FPMAS_DEFINE_GROUPS(DataGroup, ReaderWriterGroup);
FPMAS_DEFINE_LAYERS(RW_TO_DATA);

void build_model(fpmas::model::Model<SYNC_MODE>& model, fpmas::api::model::AgentGroup& group);
void print_write_operations_count(fpmas::api::communication::MpiCommunicator& comm, fpmas::api::model::AgentGroup& group);

Behavior<ReaderWriterBehavior> behavior {&ReaderWriterBehavior::behavior};

int main(int argc, char** argv) {
	FPMAS_REGISTER_AGENT_TYPES(AGENT_TYPES)
	fpmas::init(argc, argv);
	{
		// Defines a default model
		fpmas::model::Model<SYNC_MODE> model;

		// Defines an agent group
		fpmas::model::AgentGroup& group = model.buildGroup(ReaderWriterGroup, behavior);
		
		// Set up agents on process 0
		FPMAS_ON_PROC(model.getMpiCommunicator(), 0) {
			build_model(model, group);
		}

		// Schedules load balancing
		model.scheduler().schedule(0, model.loadBalancingJob());

		// Schedules agent group execution
		model.scheduler().schedule(0.1, 1, group.jobs());
		
		// Runs the model for 2 iterations
		model.runtime().run(4);

		print_write_operations_count(model.getMpiCommunicator(), group);
	}
	fpmas::finalize();
}

void build_model(fpmas::model::Model<SYNC_MODE>& model, fpmas::api::model::AgentGroup& group) {
	for(int i = 0; i < model.getMpiCommunicator().getSize(); i++) {
		group.add(new DataAgent(0, 0));
	}
	for(int i = 0; i < model.getMpiCommunicator().getSize(); i++) {
		auto* rw_agent = new ReaderWriterAgent;
		// Add rw_agent to the group BEFORE linking it
		group.add(rw_agent);
		for(auto* data_agent : group.agents()) {
			model.link(rw_agent, data_agent, RW_TO_DATA);
		}
	}
}

void print_write_operations_count(
		fpmas::api::communication::MpiCommunicator& comm,
		fpmas::api::model::AgentGroup& group) {
	int write_received = 0;
	for(auto* agent : group.localAgents())
		if(auto* data_agent = dynamic_cast<DataAgent*>(agent))
			write_received+=data_agent->received_write_count;

	fpmas::communication::TypedMpi<int> mpi(comm);
	int total_write_emitted_count =
		fpmas::communication::reduce(mpi, 0, ReaderWriterAgent::emitted_write_count);
	int total_write_received_count =
		fpmas::communication::reduce(mpi, 0, write_received);
	FPMAS_ON_PROC(comm, 0) {
		std::cout
			<< "Total write operations emitted: "
			<< total_write_emitted_count << std::endl;
		std::cout
			<< "Total write operations received: "
			<< total_write_received_count << std::endl;
	}
}
