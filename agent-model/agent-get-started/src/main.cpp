#include "fpmas.h"
#include "agents.h"

#define NUM_STEP 4

FPMAS_JSON_SET_UP(Agent)

using fpmas::model::Model;
using fpmas::synchro::HardSyncMode;
using fpmas::model::AgentGroup;
using fpmas::model::Behavior;

FPMAS_DEFINE_GROUPS(GROUP);

int main(int argc, char** argv) {
	FPMAS_REGISTER_AGENT_TYPES(Agent);

	fpmas::init(argc, argv);
	{
		// Instantiates a Model
		Model<HardSyncMode> model;

		// Agent Behavior
		Behavior<Agent> behavior {&Agent::behavior};
		// Build a new agent group associated to behavior
		AgentGroup& agent_group = model.buildGroup(GROUP, behavior);

		// Adds two Agents to the group
		agent_group.add(new Agent);
		agent_group.add(new Agent);

		// Schedules the group to be executed at each iteration
		model.scheduler().schedule(0, 1, agent_group.jobs());

		// Runs 4 iterations of the model
		model.runtime().run(NUM_STEP);
	}
	fpmas::finalize();
}
