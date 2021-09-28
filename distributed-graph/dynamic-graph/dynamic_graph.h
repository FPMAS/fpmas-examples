#include "fpmas.h"
#include "../utils/utils.h"

FPMAS_DEFINE_LAYERS(INIT_LAYER, DYNAMIC_LAYER);

extern std::unordered_map<int, std::string> layers;

void init_graph(
		std::array<DistributedId, 5>& nodes,
		std::array<DistributedId, 4>& edges,
		fpmas::api::graph::DistributedGraph<int>& graph);
