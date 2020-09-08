#include "fpmas.h"

#define _STRING(X) #X
#define STRING(X) _STRING(X)

void print_local_graph(
		fpmas::api::graph::DistributedGraph<int>& graph,
		std::unordered_map<int, std::string> layer_names
		);
void print_global_graph(
		fpmas::api::communication::MpiCommunicator& comm,
		fpmas::api::graph::DistributedGraph<int>& graph,
		std::unordered_map<int, std::string> layer_names
		);
void print_banner(std::string text);
