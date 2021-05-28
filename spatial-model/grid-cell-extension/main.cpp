#include "agents.h"

using fpmas::synchro::HardSyncMode;

#define AGENT_TYPES GrowingGridCell::JsonBase, EatingGridAgent::JsonBase

FPMAS_JSON_SET_UP(AGENT_TYPES);

FPMAS_DEFINE_GROUPS(GROW, EAT);

int main(int argc, char** argv) {
	FPMAS_REGISTER_AGENT_TYPES(AGENT_TYPES);

	fpmas::init(argc, argv);
	{
		// GridModel using GrowingGridCell as cells
		GridModel<HardSyncMode, GrowingGridCell> model;

		// The VonNeumannGridBuilder will build GrowingGridCell instances
		VonNeumannGridBuilder<GrowingGridCell> grid_builder(
				3*model.getMpiCommunicator().getSize(), // width
				3 // height
				);

		// GrowingGridCell behavior
		fpmas::model::Behavior<GrowingGridCell> grow_behavior {
			&GrowingGridCell::grow
		};
		// Cell group associated to the grow behavior
		auto& grow_group = model.buildGroup(GROW, grow_behavior);
		// Builds the grid and adds cells to `grow_group`
		grid_builder.build(model, {grow_group});

		// GridAgentExample behavior
		fpmas::model::Behavior<EatingGridAgent> eat_behavior {
			&EatingGridAgent::eat
		};
		// Builds a new MoveAgentGroup associated to move_behavior
		auto& eat_group = model.buildMoveGroup(EAT, eat_behavior);

		// Random uniform mapping for the built grid
		UniformGridAgentMapping mapping(
				grid_builder.width(), grid_builder.height(), // Grid size
				2*model.getMpiCommunicator().getSize() // Agent count
				);
		// Build agent instances with a `new GridAgentExample` statement
		DefaultSpatialAgentFactory<EatingGridAgent> factory;
		// Initializes GridAgentExamples on the grid (distributed process)
		GridAgentBuilder<GrowingGridCell>().build(
				model, {eat_group}, factory, mapping
				);

		model.scheduler().schedule(0.1, 1, grow_group.jobs());
		model.scheduler().schedule(0.2, 1, eat_group.jobs());

		model.runtime().run(5);
	}
	fpmas::finalize();
}
