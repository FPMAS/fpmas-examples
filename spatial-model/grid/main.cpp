#include "agents.h"

#define AGENT_TYPES fpmas::model::GridCell::JsonBase, GridAgentExample::JsonBase

FPMAS_JSON_SET_UP(AGENT_TYPES);

using namespace fpmas::model;
using fpmas::synchro::HardSyncMode;

FPMAS_DEFINE_GROUPS(MOVE);

int main(int argc, char** argv) {
	FPMAS_REGISTER_AGENT_TYPES(AGENT_TYPES);

	// Used to seed global random generators
	fpmas::seed(549);

	fpmas::init(argc, argv);
	{
		// Defines a new GridModel
		GridModel<HardSyncMode> model;
		// Defines a grid builder, that will build a grid of size (4*num_procs)x4
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
		Behavior<GridAgentExample> move_behavior {
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
		// Initializes GridAgentExamples on the grid (distributed process).
		// All agents are automatically added to the move_group.
		GridAgentBuilder<>().build(
				model, {move_group}, factory, mapping
				);
		model.graph().synchronize();


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
