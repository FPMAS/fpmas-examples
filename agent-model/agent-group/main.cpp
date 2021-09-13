#include "fpmas.h"
#include "agents.h"
#include <thread>
#include <chrono>

using fpmas::synchro::HardSyncMode;

using fpmas::communication::MpiCommunicator;
using fpmas::model::AgentGroup;
using fpmas::model::Behavior;
using fpmas::model::Model;

FPMAS_JSON_SET_UP(Agent1, Agent2);
FPMAS_DEFINE_GROUPS(G0, G1);

void print_agents(const AgentGroup& group);

int main(int argc, char** argv) {
	FPMAS_REGISTER_AGENT_TYPES(Agent1, Agent2);
	fpmas::init(argc, argv);
	{
		Model<HardSyncMode> model;

		Behavior<AgentBehavior1> behavior_1 {&AgentBehavior1::behavior_1};
		Behavior<Agent1> behavior_0 {&Agent1::behavior_0};

		AgentGroup& group_0 = model.buildGroup(G0, behavior_0);
		AgentGroup& group_1 = model.buildGroup(G1, behavior_1);

		Agent1* shared_agent_1 = new Agent1;
		// Adds two Agent1 to group_0 on each process
		group_0.add(shared_agent_1); // Belongs to group 0 and 1
		group_0.add(new Agent1); // Belongs only to group 0

		// Adds an Agent1 and an Agent2 to group_1 on each process
		group_1.add(shared_agent_1); // Belongs to group 0 and 1
		group_1.add(new Agent2); // Belongs only to group 1

		print_agents(group_0);
		print_agents(group_1);
	}
	fpmas::finalize();
}

void print_agents(const AgentGroup& group) {
	auto& comm = fpmas::communication::WORLD;
	for(int rank = 0; rank < comm.getSize(); rank++) {
		FPMAS_ON_PROC(comm, rank) {
			std::cout
				<< "Group " << group.groupId() << " agents on process "
				<< comm.getRank() << ":" << std::endl;
			for(auto agent : group.localAgents()) {
				std::cout
					<< "- ID: " << agent->node()->getId()
					<< ", Type: " << agent->typeId().name()
					<< std::endl;
			}
			if(rank == comm.getSize()-1)
				std::cout << std::endl;
		}
		comm.barrier();
	}
	std::this_thread::sleep_for(std::chrono::duration<double>(.5));
}
