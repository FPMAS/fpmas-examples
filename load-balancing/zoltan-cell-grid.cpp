#include "fpmas.h"

FPMAS_DEFINE_GROUPS(AGENT_GROUP);

/**
 * Example spatial agent without any behavior.
 */
struct Agent : public fpmas::model::GridAgent<Agent> {
	// For this example, the Agent does not perceive anything
	static const fpmas::model::VoidRange<fpmas::model::GridCell> perception_range;
	// This range allows agent to move to cells in the Von Neumann neighborhood.
	static const fpmas::model::VonNeumannRange<fpmas::model::VonNeumannGrid<>> move_range;

	FPMAS_PERCEPTION_RANGE(perception_range);
	FPMAS_MOBILITY_RANGE(move_range);
};
// Range initialization
const fpmas::model::VoidRange<fpmas::model::GridCell> Agent::perception_range;
const fpmas::model::VonNeumannRange<fpmas::model::VonNeumannGrid<>> Agent::move_range(1);

FPMAS_DEFAULT_JSON(Agent);

FPMAS_JSON_SET_UP(Agent::JsonBase, fpmas::model::GridCell::JsonBase);

int main(int argc, char** argv) {
	FPMAS_REGISTER_AGENT_TYPES(Agent::JsonBase, fpmas::model::GridCell::JsonBase);

	fpmas::init(argc, argv);
	{
		// Zoltan algorithm
		fpmas::model::ZoltanLoadBalancing zoltan(fpmas::communication::WORLD);
		// Zoltan Cell algorithm
		fpmas::model::CellLoadBalancing zoltan_cell(fpmas::communication::WORLD, zoltan);


		// Grid Model initialized with zoltan, so that model.loadBalancingJob()
		// is bound to Zoltan
		fpmas::model::GridModel<fpmas::synchro::GhostMode> model(zoltan_cell);

		// Initializes a group without behavior
		fpmas::model::IdleBehavior behavior;
		auto& agent_group = model.buildMoveGroup(AGENT_GROUP, behavior);

		// Builds a 5x5 VonNeumann Grid (distributed process)
		fpmas::model::VonNeumannGrid<>::Builder(5, 5)
			.build(model);

		// Uniformly distributes 10 agents on the 5x5 grid
		fpmas::model::UniformGridAgentMapping agent_mapping(5, 5, 10);
		// Builds and initializes agents (distributed process)
		fpmas::model::GridAgentBuilder<>().build(
				model, {agent_group}, [] () {return new Agent;}, agent_mapping
				);

		// Schedules Zoltan load balancing at each iteration
		model.scheduler().schedule(0, 1, model.loadBalancingJob());
		// Run 5 iterations
		model.runtime().run(5);

		// Graph output
		fpmas::io::FileOutput json_output(
				"zoltan-cell-grid.%r.json",
				model.getMpiCommunicator().getRank()
				);
		fpmas::io::JsonOutput<fpmas::api::model::AgentGraph&>(
				json_output,
				[&model] () -> fpmas::api::model::AgentGraph& {return model.graph();}
				).dump();

	}
	fpmas::finalize();
}
