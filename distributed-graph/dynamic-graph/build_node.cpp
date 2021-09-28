#include "dynamic_graph.h"


using fpmas::synchro::SYNC_MODE;

FPMAS_JSON_SET_UP();

int main(int argc, char** argv) {

	fpmas::init(argc, argv);
	{
		fpmas::communication::MpiCommunicator comm;
		fpmas::graph::DistributedGraph<int, SYNC_MODE> graph {comm};
		std::array<DistributedId, 5> nodes;
		std::array<DistributedId, 4> edges;

		FPMAS_ON_PROC(comm, 0) {
			std::cout << "== SYNC_MODE : " << STRING(SYNC_MODE) << std::endl;
			std::cout << std::endl;
			print_banner("Initial Distribution");
		}
		init_graph(nodes, edges, graph);
		print_global_graph(comm, graph, layers);

		FPMAS_ON_PROC(comm, 0) {
			auto n_2 = graph.getNode(nodes[2]);
			// Binds task t to n_2
			auto t = FPMAS_NODE_TASK(n_2, {
					auto n_6 = graph.buildNode(0);
					// Links n_2 to the new node
					graph.link(n_2, n_6, DYNAMIC_LAYER);

					// Links node_2 to n_3 and n_4
					for(auto node : n_2->outNeighbors(INIT_LAYER))
					graph.link(n_6, node, DYNAMIC_LAYER);
					});
			// Run the task on process 0
			t.run();
		}
		// Synchronize the graph from all processes
		graph.synchronize();

		FPMAS_ON_PROC(comm, 0) {
			print_banner("Final Distribution");
		}
		print_global_graph(comm, graph, layers);
	}
	fpmas::finalize();
}

