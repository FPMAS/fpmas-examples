/* src/main.cpp */

#include "fpmas.h"
#include "agents.h"


FPMAS_JSON_SET_UP(Agent)

using fpmas::communication::MpiCommunicator;
using fpmas::synchro::HardSyncMode;
using fpmas::model::AgentGroup;
using fpmas::model::Behavior;

FPMAS_DEFINE_GROUPS(GROUP);

/*
 * Utility function used to print agents of the group using json serialization.
 */
void print_agents(const AgentGroup& group, int rank) {
	// Initializes empty json array
	nlohmann::json json_agents = nlohmann::json::array();
	// Pushes (and serialize) agents into the json array
	for(auto agent : group.agents())
		json_agents.push_back(agent->node()->data());
	// Prints
	std::cout << "[Proc " << rank << "] Agents :" << std::endl;
	std::cout << json_agents.dump(4) << std::endl;
}

int main(int argc, char** argv) {
	FPMAS_REGISTER_AGENT_TYPES(Agent);

	fpmas::init(argc, argv);
	{
		// Instantiates a DefaultModel
		fpmas::model::Model<HardSyncMode> model;
		fpmas::api::communication::MpiCommunicator& comm = model.getMpiCommunicator();

		// Agent Behavior
		Behavior<Agent> behavior {&Agent::behavior};
		// Build a new agent group
		AgentGroup& agent_group = model.buildGroup(GROUP, behavior);

		// Initializes 2 agents on proc 0
		FPMAS_ON_PROC(comm, 0) {
			agent_group.add(new Agent(0, "message_1"));
			agent_group.add(new Agent(1, "message_2"));
		}

		// Print initial agent distribution
		print_agents(agent_group, comm.getRank());

		// Initializes a new partition map on all processes
		fpmas::api::graph::PartitionMap map;

		FPMAS_ON_PROC(comm, 0) {
			// On proc 0, assigns the first agent of the group to process 1
			map[agent_group.localAgents()[0]->node()->getId()] = 1;

			// The other agent is implicitly left on the current process
		}

		// Distributes agent nodes.
		// According to the map above, the first agent on process 0 is sent to
		// process 1
		std::cout << "[Proc " << comm.getRank() << "] Distributing agents..." << std::endl;
		model.graph().distribute(map);

		// Prints final distribution
		print_agents(agent_group, comm.getRank());
	}
	fpmas::finalize();
}
