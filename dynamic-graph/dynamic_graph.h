#include "fpmas.h"

#define INIT_LAYER 0
#define DYNAMIC_LAYER 1
#define _STRING(X) #X
#define STRING(X) _STRING(X)

void print_local_graph(fpmas::api::graph::DistributedGraph<int>& graph);
void print_global_graph(
		fpmas::api::communication::MpiCommunicator& comm,
		fpmas::api::graph::DistributedGraph<int>& graph);

void init_graph(
		std::array<DistributedId, 5>& nodes,
		std::array<DistributedId, 4>& edges,
		fpmas::api::graph::DistributedGraph<int>& graph);
