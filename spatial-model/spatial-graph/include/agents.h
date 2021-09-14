#include "fpmas/model/spatial/graph.h"

using namespace fpmas::model;

class Agent : public SpatialAgent<Agent, GraphCell> {
	public:
		static const GraphRange<> mobility_range;
		static const GraphRange<> perception_range;

		FPMAS_MOBILITY_RANGE(mobility_range);
		FPMAS_PERCEPTION_RANGE(perception_range);

		void move();
};

FPMAS_DEFAULT_JSON(Agent);
