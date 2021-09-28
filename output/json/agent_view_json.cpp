#include "fpmas.h"
#include "agent_view.h"

FPMAS_JSON_SET_UP(Agent);

using fpmas::api::utils::PtrWrapper;

FPMAS_DEFINE_GROUPS(GROUP_0);

int main(int argc, char** argv) {
	FPMAS_REGISTER_AGENT_TYPES(Agent)
	fpmas::init(argc, argv);
	{
		// Model definition
		fpmas::model::Model<fpmas::synchro::GhostMode> model;
		fpmas::model::Behavior<Agent> agent_behavior(&Agent::generate_new_message);
		auto& group = model.buildGroup(GROUP_0, agent_behavior);

		// Random graph generation
		fpmas::random::PoissonDistribution<std::size_t> edge_dist(3);
		fpmas::model::DistributedUniformGraphBuilder graph_builder(edge_dist);
		fpmas::model::DistributedAgentNodeBuilder agent_node_builder(
				group, // Group to which agents should be added
				2*model.getMpiCommunicator().getSize(), // Total agent count
				[] () {return new Agent;}, // Agent allocator
				model.getMpiCommunicator() // MPI communicator
				);
		graph_builder.build(agent_node_builder, AGENT_CONTACT, model.graph());

		// Opens a distinct file on each process
		fpmas::io::DynamicFileOutput file(
				"agent.%r.%t.json",
				model.getMpiCommunicator(),
				model.runtime()
				);
		// JsonOutput definition
		fpmas::io::JsonOutput<std::vector<AgentView>> output(
				// dynamic output stream
				file,
				// Lambda function based Watcher: fetches LOCAL agents in the
				// group
				[&group] () {
				std::vector<AgentView> vec;
				for(auto agent
						: fpmas::utils::ptr_wrapper_cast<Agent>(group.localAgents()))
					vec.emplace_back(agent);
				return vec;
				},
				true // Automatically indents JSON output
				);

		// Behavior execution
		model.scheduler().schedule(0, 1, group.jobs());
		// Json output
		model.scheduler().schedule(0.1, 1, output.job());

		// Runs 2 time steps of the model
		model.runtime().run(2);
	}
	fpmas::finalize();
}
