#include "fpmas.h"
#include "../utils/utils.h"

using fpmas::synchro::HardSyncMode;
using fpmas::synchro::GhostMode;

std::unordered_map<int, std::string> layers {{0, "DEFAULT_LAYER"}};

FPMAS_DEFINE_LAYERS(DEFAULT_LAYER);

FPMAS_JSON_SET_UP();

int main(int argc, char** argv) {
	fpmas::init(argc, argv);
	{
		fpmas::communication::MpiCommunicator comm;
		fpmas::graph::DistributedGraph<int, SYNC_MODE> graph {comm};

		fpmas::api::graph::PartitionMap partition;
		FPMAS_ON_PROC(comm, 0) {
			// Builds a "ring"
			std::vector<fpmas::api::graph::DistributedNode<int>*> nodes;
			for(int i = 0; i < comm.getSize(); i++) {
				auto node = graph.buildNode(i);
				nodes.push_back(node);
				// Each node of the ring is associated to a process
				partition[node->getId()] = i;
			}

			for(int i = 0; i < comm.getSize(); i++)
				graph.link(nodes[i], nodes[(i+1) % comm.getSize()], DEFAULT_LAYER);
		}
		// An extra node build on each process, ignored in the partition
		graph.buildNode(0);

		FPMAS_ON_PROC(comm, 0)
			print_banner("Initial Distribution");
		print_global_graph(comm, graph, layers);

		// Distributes the graph according to the partition
		// Notice that the partition is empty for all processes except 0
		graph.distribute(partition);

		FPMAS_ON_PROC(comm, 0)
			print_banner("Final Distribution");
		print_global_graph(comm, graph, layers);
	}
	fpmas::finalize();
}
