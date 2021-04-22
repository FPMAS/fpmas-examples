#include "fpmas.h"
#include "agents.h"

#define NUM_STEP 4
#define AGENT_TYPES Agent1, Agent2

FPMAS_JSON_SET_UP(AGENT_TYPES)

using fpmas::model::Model;
using fpmas::synchro::HardSyncMode;
using fpmas::model::AgentGroup;

FPMAS_DEFINE_GROUPS(Group);

int main(int argc, char** argv) {
	FPMAS_REGISTER_AGENT_TYPES(AGENT_TYPES);

	fpmas::init(argc, argv);
	{
		// Instantiates a Model
		Model<HardSyncMode> model;

		// Build a new agent group
		AgentGroup& agent_group = model.buildGroup(Group);

		// On each process, adds an agent of each type
		agent_group.add(new Agent1);
		agent_group.add(new Agent2);

		// Schedules the group to be executed at each iteration
		model.scheduler().schedule(0, 1, agent_group.jobs());

		// Runs 4 iterations of the model
		model.runtime().run(NUM_STEP);
	}
	fpmas::finalize();
}
