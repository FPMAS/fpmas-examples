#include "fpmas.h"
#include "agents.h"
#include <thread>
#include <chrono>

using fpmas::synchro::HardSyncMode;

using fpmas::communication::MpiCommunicator;
using fpmas::model::AgentGroup;

FPMAS_JSON_SET_UP(Agent1, Agent2);
FPMAS_DEFINE_GROUPS(G1, G2);

void print_agents(const AgentGroup& group, MpiCommunicator& comm);

int main(int argc, char** argv) {
	FPMAS_REGISTER_AGENT_TYPES(Agent1, Agent2);
	fpmas::init(argc, argv);
	{
		fpmas::model::Model<HardSyncMode> model;

		AgentGroup& group_1 = model.buildGroup(G1);
		AgentGroup& group_2 = model.buildGroup(G2);

		// Adds two Agent1 to group_1 on each process
		group_1.add(new Agent1);
		group_1.add(new Agent1);

		// Adds an Agent1 and an Agent2 to group_2 on each process
		group_2.add(new Agent1);
		group_2.add(new Agent2);

		print_agents(group_1, model.getMpiCommunicator());
		print_agents(group_2, model.getMpiCommunicator());
	}
	fpmas::finalize();
}

void print_agents(const AgentGroup& group, MpiCommunicator& comm) {
	for(int rank = 0; rank < comm.getSize(); rank++) {
		FPMAS_ON_PROC(comm, rank) {
			std::cout
				<< "Group " << group.groupId() << " agents on process "
				<< comm.getRank() << ":" << std::endl;
			for(auto agent : group.localAgents()) {
				std::cout
					<< "- ID: " << agent->get()->node()->getId()
					<< ", Type: " << agent->get()->typeId().name()
					<< std::endl;
			}
			if(rank == comm.getSize()-1)
				std::cout << std::endl;
		}
		comm.barrier();
	}
	std::this_thread::sleep_for(std::chrono::duration<double>(.5));
}
