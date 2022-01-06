#include "fpmas.h"

FPMAS_DEFINE_GROUPS(AGENT_GROUP);

/**
 * Example spatial agent without any behavior.
 */
struct Agent : public fpmas::model::SpatialAgent<Agent, fpmas::model::GraphCell> {
	// For this example, the Agent does not perceive anything
	static const fpmas::model::VoidRange<fpmas::model::GraphCell> perception_range;
	// This range allows agent to move to neighboring graph cells.
	static const fpmas::model::GraphRange<fpmas::model::GraphCell> move_range;

	FPMAS_MOBILITY_RANGE(move_range);
	FPMAS_PERCEPTION_RANGE(perception_range);
};
FPMAS_DEFAULT_JSON(Agent);

// range initialization
const fpmas::model::VoidRange<fpmas::model::GraphCell> Agent::perception_range;
const fpmas::model::GraphRange<fpmas::model::GraphCell> Agent::move_range(
		// Exludes the current location from the range
		fpmas::model::EXCLUDE_LOCATION
		);

FPMAS_JSON_SET_UP(Agent::JsonBase, fpmas::model::GraphCell::JsonBase);

int main(int argc, char** argv) {
	FPMAS_REGISTER_AGENT_TYPES(Agent::JsonBase, fpmas::model::GraphCell::JsonBase);

	fpmas::init(argc, argv);
	{
		// Zoltan algorithm
		fpmas::model::ZoltanLoadBalancing zoltan(fpmas::communication::WORLD);
		// Model initialized with zoltan, so that model.loadBalancingJob() is
		// bound to Zoltan
		fpmas::model::SpatialModel<fpmas::synchro::GhostMode, fpmas::model::GraphCell>
			model(zoltan);

		// Defines a group without any behavior
		fpmas::model::IdleBehavior behavior;
		auto& agent_group = model.buildMoveGroup(AGENT_GROUP, behavior);

		// Spatial graph building
		{
			// 2 outgoing edges by agent in average
			fpmas::random::PoissonDistribution<> edge_dist(2);
			fpmas::model::DistributedUniformGraphBuilder graph_builder(edge_dist);

			// Distributed cell builder.
			fpmas::model::DistributedAgentNodeBuilder cell_builder(
					// Group to which cells are added
					model.cellGroup(),
					// TOTAL cell count
					3*model.getMpiCommunicator().getSize(),
					// Function used to allocate cells
					[] () {return new fpmas::model::GraphCell;},
					// MPI communicator
					model.getMpiCommunicator()
					);

			// Builds the cell graph (distributed process)
			graph_builder.build(
					cell_builder, fpmas::api::model::CELL_SUCCESSOR, model.graph()
					);
			// Required synchronization to enable GraphRange usage
			fpmas::model::GraphRange<fpmas::model::GraphCell>::synchronize(model);
		}

		// Spatial agents initialization
		{
			// A mapping that uniformly distribute agents among previously
			// built cells
			fpmas::model::UniformAgentMapping mapping(
					model.getMpiCommunicator(), model.cellGroup(),
					2*model.getMpiCommunicator().getSize() // TOTAL agent count
					);

			// Builds spatial agents (distributed process)
			fpmas::model::SpatialAgentBuilder<fpmas::model::GraphCell>().build(
					model, {agent_group},
					[] () {return new Agent;},
					mapping
					);
		}

		// Schedules Zoltan load balancing at each iteration
		model.scheduler().schedule(0, 1, model.loadBalancingJob());
		// Run 5 iterations
		model.runtime().run(5);

		// Graph output
		fpmas::io::FileOutput json_output(
				"zoltan-spatial-graph.%r.json",
				model.getMpiCommunicator().getRank()
				);
		fpmas::io::JsonOutput<fpmas::api::model::AgentGraph&>(
				json_output,
				[&model] () -> fpmas::api::model::AgentGraph& {return model.graph();}
				).dump();
	}
	fpmas::finalize();
}
