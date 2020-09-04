#include "dynamic_graph.h"

using fpmas::synchro::SYNC_MODE;

int main(int argc, char** argv) {

	fpmas::init(argc, argv);
	{
		fpmas::communication::MpiCommunicator comm;
		fpmas::DistributedGraph<int, SYNC_MODE> graph {comm};
		std::array<DistributedId, 5> nodes;
		std::array<DistributedId, 4> edges;

		FPMAS_ON_PROC(comm, 0) {
			std::cout << "== SYNC_MODE : " << STRING(SYNC_MODE) << std::endl;
			std::cout << std::endl;
			std::cout << "==========================" << std::endl;
			std::cout << "== Initial distribution ==" << std::endl;
			std::cout << "==========================" << std::endl;
		}
		init_graph(nodes, edges, graph);
		print_global_graph(comm, graph);

		FPMAS_ON_PROC(comm, 0) {
			auto n_2 = graph.getNode(nodes[2]);
			// Binds task t to n_2
			auto t = FPMAS_NODE_TASK(n_2, {
					// Unlinks edges from n_0 to n_2
					graph.unlink(graph.getEdge(edges[0]));

					// Unlinks edges from n_2 to n_3
					graph.unlink(graph.getEdge(edges[2]));

					// Unlinks edges from n_2 to n_4
					graph.unlink(graph.getEdge(edges[3]));
					
					});
			// Run the task on process 0
			t.run();
		}
		// Synchronize the graph from all processes
		graph.synchronize();

		FPMAS_ON_PROC(comm, 0) {
			std::cout << "==========================" << std::endl;
			std::cout << "==  Final distribution  ==" << std::endl;
			std::cout << "==========================" << std::endl;
		}
		print_global_graph(comm, graph);
	}
	fpmas::finalize();
}
