#include "utils.h"
#include <thread>
#include <chrono>

void print_local_graph(
		fpmas::api::graph::DistributedGraph<int>& graph,
		std::unordered_map<int, std::string> layer_names
		) {
	std::cout << "== [Process " << graph.getMpiCommunicator().getRank() << "] ==" << std::endl;
	std::cout << "== Local Nodes :" << std::endl;
	for(auto node : graph.getNodes())
		std::cout << "- " << node.first << " [" << node.second->state() << "]" << std::endl;
	std::cout << "== Local edges :" << std::endl;
	for(auto edge : graph.getEdges())
		std::cout << "- " << edge.first << " : "
			<< edge.second->getSourceNode()->getId() << " -> "
			<< edge.second->getTargetNode()->getId()
			<< " (" << layer_names[edge.second->getLayer()] << ")" << std::endl;
	std::cout << std::endl;
}

void print_global_graph(
		fpmas::api::communication::MpiCommunicator& comm,
		fpmas::api::graph::DistributedGraph<int>& graph,
		std::unordered_map<int, std::string> layer_names
		) {
	for(int i = 0; i < comm.getSize(); i++) {
		FPMAS_ON_PROC(comm, i)
			print_local_graph(graph, layer_names);
		comm.barrier();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void print_banner(std::string text) {
	for(std::size_t i = 0; i < text.length()+6; i++)
		std::cout << "=";
	std::cout << std::endl;
	std::cout << "== " << text << " ==" << std::endl;
	for(std::size_t i = 0; i < text.length()+6; i++)
		std::cout << "=";
	std::cout << std::endl << std::endl;

}
