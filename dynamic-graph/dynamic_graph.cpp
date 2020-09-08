#include "dynamic_graph.h"
#include <thread>
#include <chrono>

std::unordered_map<int, std::string> layers {{0, "INIT_LAYER"}, {1, "DYNAMIC_LAYER"}};

void init_graph(
		std::array<DistributedId, 5>& nodes,
		std::array<DistributedId, 4>& edges,
		fpmas::api::graph::DistributedGraph<int>& graph) {
	graph.clear();
	fpmas::api::graph::PartitionMap partition;
	FPMAS_ON_PROC(graph.getMpiCommunicator(), 0) {
		for(int i = 0; i < 5; i++)
			nodes[i] = graph.buildNode(0)->getId();

		auto n_2 = graph.getNode(nodes[2]);
		edges[0] = graph.link(graph.getNode(nodes[0]), n_2, INIT_LAYER)->getId();
		edges[1] = graph.link(graph.getNode(nodes[1]), n_2, INIT_LAYER)->getId();
		edges[2] = graph.link(n_2, graph.getNode(nodes[3]), INIT_LAYER)->getId();
		edges[3] = graph.link(n_2, graph.getNode(nodes[4]), INIT_LAYER)->getId();

		partition[nodes[0]] = 1;
		partition[nodes[1]] = 1;
		partition[nodes[2]] = 0;
		partition[nodes[3]] = 1;
		partition[nodes[4]] = 1;
	}
	graph.distribute(partition);
}
