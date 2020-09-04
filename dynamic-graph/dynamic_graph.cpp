#include "dynamic_graph.h"
#include <thread>
#include <chrono>

void print_local_graph(fpmas::api::graph::DistributedGraph<int>& graph) {
	std::cout << "== [Process " << graph.getMpiCommunicator().getRank() << "] ==" << std::endl;
	std::cout << "== Local Nodes :" << std::endl;
	for(auto node : graph.getNodes())
		std::cout << "- " << node.first << " [" << node.second->state() << "]" << std::endl;
	std::cout << "== Local edges :" << std::endl;
	for(auto edge : graph.getEdges())
		std::cout << "- " << edge.first << " : "
			<< edge.second->getSourceNode()->getId() << " -> "
			<< edge.second->getTargetNode()->getId()
			<< " (" << (edge.second->getLayer() == INIT_LAYER ? "INIT_LAYER" : "DYNAMIC_LAYER") << ")" << std::endl;
	std::cout << std::endl;
}

void print_global_graph(
		fpmas::api::communication::MpiCommunicator& comm,
		fpmas::api::graph::DistributedGraph<int>& graph) {
	FPMAS_ON_PROC(comm, 0)
		print_local_graph(graph);
	comm.barrier();
	
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	FPMAS_ON_PROC(comm, 1)
		print_local_graph(graph);
}

void init_graph(
		std::array<DistributedId, 5>& nodes,
		std::array<DistributedId, 4>& edges,
		fpmas::api::graph::DistributedGraph<int>& graph) {
	graph.clear();
	fpmas::api::load_balancing::PartitionMap partition;
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
