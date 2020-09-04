#include "dynamic_graph.h"


int main(int argc, char** argv) {

	fpmas::init(argc, argv);
	{
		fpmas::communication::MpiCommunicator comm;
		fpmas::DistributedGraph<int, HardSyncMode> graph {comm};
		std::array<DistributedId, 5> nodes;

		FPMAS_ON_PROC(comm, 0) {
			std::cout << "==========================" << std::endl;
			std::cout << "== Initial distribution ==" << std::endl;
			std::cout << "==========================" << std::endl;
		}
		init_graph(nodes, graph);
		print_global_graph(comm, graph);

		FPMAS_ON_PROC(comm, 0) {
			auto n_2 = graph.getNode(nodes[2]);
			// Binds task t to node
			auto t = FPMAS_NODE_TASK(n_2, {
					auto n_6 = graph.buildNode(0);
					graph.link(n_2, n_6, DYNAMIC_LAYER);

					// Links node_2 to n_3 and n_4
					for(auto node : n_2->outNeighbors(INIT_LAYER))
					graph.link(n_6, node, DYNAMIC_LAYER);
					});
			t.run();
		}
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

