#include "agents.h"

#define AGENT_TYPES fpmas::model::GridCell::JsonBase, GridAgentExample::JsonBase

FPMAS_JSON_SET_UP(AGENT_TYPES);

using fpmas::synchro::HardSyncMode;

FPMAS_DEFINE_GROUPS(MOVE);

int main(int argc, char** argv) {
	fpmas::init(argc, argv);
	FPMAS_REGISTER_AGENT_TYPES(AGENT_TYPES);
	{
		// Used to seed the global random neighbors selection
		RandomNeighbors::seed(5489);

		// Defines a new GridModel
		GridModel<HardSyncMode> model;
		// Defines a grid builder, that will build a grid of size (8*num_procs)x8
		VonNeumannGridBuilder<> grid_builder(
				4*model.getMpiCommunicator().getSize(),
				4
				);
		// Builds the grid (distributed process)
		grid_builder.build(model);

		// Initial grid output
		{
			fpmas::io::DynamicFileOutput grid_file(
					"grid.%r.json", model.getMpiCommunicator(), model.runtime()
					);
			// JSON output for the underlying graph
			fpmas::io::JsonOutput<fpmas::api::model::AgentGraph&> output(
					grid_file, [&model] () -> fpmas::api::model::AgentGraph& {return model.graph();}
					);
			// Executes JSON output
			model.runtime().execute(output.job());
		}

		// GridAgentExample behavior
		fpmas::model::Behavior<GridAgentExample> move_behavior {
			&GridAgentExample::move
		};
		// Builds a new MoveAgentGroup associated to move_behavior
		auto& move_group = model.buildMoveGroup(MOVE, move_behavior);

		// Random uniform mapping for the built grid
		UniformGridAgentMapping mapping(
				grid_builder.width(), grid_builder.height(), // Grid size
				2*model.getMpiCommunicator().getSize() // Agent count
				);
		// Build agent instances with a `new GridAgentExample` statement
		DefaultSpatialAgentFactory<GridAgentExample> factory;
		// Initializes GridAgentExamples on the grid (distributed process)
		GridAgentBuilder<>().build(
				model, {move_group}, factory, mapping
				);


		// Dynamic model output
		fpmas::io::DynamicFileOutput file(
				"graph.%r.%t.json", model.getMpiCommunicator(), model.runtime()
				);
		fpmas::io::JsonOutput<fpmas::api::model::AgentGraph&> output(
				file, [&model] () -> fpmas::api::model::AgentGraph& {return model.graph();}
				);

		// Schedules json output
		model.scheduler().schedule(0, 1, output.job());
		// Schedules GridAgentExamples execution
		model.scheduler().schedule(0.1, 1, move_group.jobs());

		// Runs the model for 5 iterations
		model.runtime().run(5);
	}
	fpmas::finalize();
}
