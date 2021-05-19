#include "fpmas/model/spatial/graph.h"

using namespace fpmas::model;

class Agent : public SpatialAgent<Agent, GraphCell> {
	public:
		static const GraphRange<> mobility_range;
		static const GraphRange<> perception_range;

		Agent() : SpatialAgent<Agent, GraphCell>(mobility_range, perception_range) {}

		void move();
};

FPMAS_DEFAULT_JSON(Agent);
