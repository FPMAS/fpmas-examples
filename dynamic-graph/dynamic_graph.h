#include "fpmas.h"

#define INIT_LAYER 0
#define DYNAMIC_LAYER 1

using fpmas::synchro::HardSyncMode;

void print_local_graph(fpmas::api::graph::DistributedGraph<int>& graph);
void print_global_graph(
		fpmas::api::communication::MpiCommunicator& comm,
		fpmas::api::graph::DistributedGraph<int>& graph);

void init_graph(
		std::array<DistributedId, 5>& nodes,
		fpmas::api::graph::DistributedGraph<int>& graph);
