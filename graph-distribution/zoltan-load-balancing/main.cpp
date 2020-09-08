#include "fpmas.h"
#include "../utils/utils.h"

#define DEFAULT_LAYER 0

using fpmas::synchro::HardSyncMode;
using fpmas::synchro::GhostMode;

std::unordered_map<int, std::string> layers {{0, "DEFAULT_LAYER"}};

int main(int argc, char** argv) {
	fpmas::init(argc, argv);
	{
		fpmas::communication::MpiCommunicator comm;
		fpmas::graph::DistributedGraph<int, SYNC_MODE> graph {comm};
		fpmas::graph::ZoltanLoadBalancing<int> zoltan_load_balancing {comm};

		FPMAS_ON_PROC(comm, 0) {
			// Builds a "ring"
			std::vector<fpmas::api::graph::DistributedNode<int>*> nodes;
			for(int i = 0; i < comm.getSize(); i++) {
				auto node = graph.buildNode(i);
				nodes.push_back(node);
			}

			for(int i = 0; i < comm.getSize(); i++)
				graph.link(nodes[i], nodes[(i+1) % comm.getSize()], DEFAULT_LAYER);
		}
		// An extra node build on each process
		graph.buildNode(0);

		FPMAS_ON_PROC(comm, 0)
			print_banner("Initial Distribution");
		print_global_graph(comm, graph, layers);

		// Distributes the graph according to the partition
		// Notice that the partition is empty for all processes except 0
		graph.balance(zoltan_load_balancing);

		FPMAS_ON_PROC(comm, 0)
			print_banner("Final Distribution");
		print_global_graph(comm, graph, layers);
	}
	fpmas::finalize();
}
