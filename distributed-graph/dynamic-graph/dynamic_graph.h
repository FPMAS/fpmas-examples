#include "fpmas.h"
#include "../utils/utils.h"

#define INIT_LAYER 0
#define DYNAMIC_LAYER 1

extern std::unordered_map<int, std::string> layers;

void init_graph(
		std::array<DistributedId, 5>& nodes,
		std::array<DistributedId, 4>& edges,
		fpmas::api::graph::DistributedGraph<int>& graph);
