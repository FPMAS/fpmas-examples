#include "fpmas.h"
#include "agents.h"

#define AGENT_TYPES Agent::JsonBase, GraphCell::JsonBase

using namespace fpmas::model;
using fpmas::synchro::HardSyncMode;

FPMAS_JSON_SET_UP(AGENT_TYPES);

FPMAS_DEFINE_GROUPS(GROUP);

Behavior<Agent> move_behavior {&Agent::move};

void init_uniform_graph(SpatialModel<HardSyncMode, GraphCell>& model);

int main(int argc, char** argv) {
	FPMAS_REGISTER_AGENT_TYPES(AGENT_TYPES);

	// A custom seed to control graph and agents initialization
	fpmas::seed(8);

	fpmas::init(argc, argv);
	{
		// Defines a default model
		SpatialModel<HardSyncMode, GraphCell> model;
		// Builds a uniform graph
		init_uniform_graph(model);

		// Initializes the GraphRange
		GraphRange<>::synchronize(model);

		// Defines an agent group
		MoveAgentGroup<GraphCell>& group
			= model.buildMoveGroup(GROUP, move_behavior);

		// Builds Agents using a `new Agent` statement
		DefaultSpatialAgentFactory<Agent> agent_factory;
		// Assigns two Agents to random GraphCells
		UniformAgentMapping mapping(
				model.getMpiCommunicator(), // MPI communicator
				model.cellGroup(), // Available cells
				2 // Number of agents to initialize
				);
		// SpatialAgentBuilder algorithm
		SpatialAgentBuilder<GraphCell> agent_builder;

		agent_builder.build(
			model, // SpatialModel
			{group}, // Groups to which each Agent must be added
			agent_factory, // Used to allocate Agents when required
			mapping // Specifies where Agents must be initialized
			);
		
		fpmas::io::DynamicFileOutput output_file(
				"graph.%r.%t.json",
				model.getMpiCommunicator(), model.runtime()
				);
		fpmas::io::JsonOutput<fpmas::api::model::AgentGraph&> json_output(
				output_file,
				[&model] () -> fpmas::api::model::AgentGraph& {return model.graph();}
				);

		// Schedules graph json output
		model.scheduler().schedule(0.1, 1, json_output.job());
		// Schedules agent group execution
		model.scheduler().schedule(0.2, 1, group.jobs());
		// Schedules other jobs
		// ...

		// Runs the model for 5 iterations
		model.runtime().run(5);
	}
	fpmas::finalize();
}

/*
 * Builds a cell graph
 */
void init_uniform_graph(SpatialModel<HardSyncMode, GraphCell>& model) {
	// Edge count distribution: uniform between 1 and 3
	fpmas::random::UniformIntDistribution<std::size_t> edge_dist(1, 3);
	// Graph builder instance
	DistributedUniformGraphBuilder builder(edge_dist);

	// Node builder: used to dynamically instantiate GraphCells on each process
	DistributedAgentNodeBuilder cell_builder(
			// Group to which Cells are added
			model.cellGroup(),
			// Cell count
			5*model.getMpiCommunicator().getSize(),
			// Cell allocator. DefaultCells are used
			[] {return new GraphCell;},
			// MPI communicator
			model.getMpiCommunicator()
			);
	// Builds the cell graph into the model.
	// Cells are linked on the CELL_SUCCESSOR layer.
	builder.build(cell_builder, fpmas::api::model::CELL_SUCCESSOR, model.graph());
}
