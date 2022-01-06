#include "fpmas.h"


FPMAS_DEFINE_GROUPS(AGENT_GROUP);
FPMAS_DEFINE_LAYERS(AGENT_LAYER);

// Example empty Agent
struct Agent : public fpmas::model::AgentBase<Agent> {
};
FPMAS_DEFAULT_JSON(Agent);

FPMAS_JSON_SET_UP(Agent);

int main(int argc, char** argv) {
	FPMAS_REGISTER_AGENT_TYPES(Agent);

	fpmas::init(argc, argv);
	{
		// Zoltan algorithm
		fpmas::model::ZoltanLoadBalancing zoltan(fpmas::communication::WORLD);
		// Model initialized with zoltan, so that model.loadBalancingJob() is
		// bound to Zoltan
		fpmas::model::Model<fpmas::synchro::GhostMode> model(zoltan);

		// Defines a group without any behavior
		auto& group = model.buildGroup(AGENT_GROUP);

		// 2 outgoing edges by agent in average
		fpmas::random::PoissonDistribution<> edge_dist(2);
		fpmas::model::DistributedUniformGraphBuilder graph_builder(edge_dist);

		// Distributed builder. In total, 3 Agent by process are built.
		fpmas::model::DistributedAgentNodeBuilder node_builder(
				group, 3*model.getMpiCommunicator().getSize(),
				[] () {return new Agent;}, model.getMpiCommunicator()
				);

		// Builds the graph (distributed process)
		graph_builder.build(node_builder, AGENT_LAYER, model.graph());

		// Schedules Zoltan load balancing at each iteration
		model.scheduler().schedule(0, 1, model.loadBalancingJob());
		// Run 5 iterations
		model.runtime().run(5);

		// Graph output
		fpmas::io::FileOutput json_output(
				"zoltan-graph.%r.json",
				model.getMpiCommunicator().getRank()
				);
		fpmas::io::JsonOutput<fpmas::api::model::AgentGraph&>(
				json_output,
				[&model] () -> fpmas::api::model::AgentGraph& {return model.graph();}
				).dump();
	}
	fpmas::finalize();
}
