/* src/main.cpp */

#include "fpmas.h"
#include "agents.h"

#define AGENT_TYPES Agent1, Agent2

FPMAS_JSON_SET_UP(AGENT_TYPES)

using fpmas::communication::MpiCommunicator;
using fpmas::synchro::HardSyncMode;
using fpmas::model::AgentGroup;

FPMAS_DEFINE_GROUPS(Group);

/*
 * Utility function used to print agents of the group using json serialization.
 */
void print_agents(const AgentGroup& group, int rank) {
	// Initializes empty json array
	nlohmann::json json_agents = nlohmann::json::array();
	// Pushes (and serizalize) agents into the json array
	for(auto agent : group.agents())
		json_agents.push_back(*agent);
	// Prints
	std::cout << "[Proc " << rank << "] Agents :" << std::endl;
	std::cout << json_agents.dump(4) << std::endl;
}

int main(int argc, char** argv) {
	FPMAS_REGISTER_AGENT_TYPES(AGENT_TYPES);

	fpmas::init(argc, argv);
	{
		// Instantiates a DefaultModel
		fpmas::model::Model<HardSyncMode> model;
		MpiCommunicator& comm = model.getMpiCommunicator();

		// Build a new agent group
		AgentGroup& agent_group = model.buildGroup(Group);

		// Initializes 3 agents on proc 0
		FPMAS_ON_PROC(comm, 0) {
			agent_group.add(new Agent1(0, "message_1"));
			agent_group.add(new Agent1(1, "message_2"));
			agent_group.add(new Agent2);
		}

		// Print initial agent distribution
		print_agents(agent_group, comm.getRank());

		// Initializes a new partition map
		fpmas::api::graph::PartitionMap map;
		// Assign each agent's node to proc 1
		for(auto agent : agent_group.agents())
			map[agent->get()->node()->getId()] = 1;

		// Distributes agent nodes
		// According to the map above, the 3 agents are sent to proc 1
		std::cout << "[Proc " << comm.getRank() << "] Distributing agents..." << std::endl;
		model.graph().distribute(map);

		// Prints final distribution
		print_agents(agent_group, comm.getRank());
	}
	fpmas::finalize();
}
