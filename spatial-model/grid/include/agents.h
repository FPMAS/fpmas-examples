#include "fpmas.h"

using namespace fpmas::model;

class GridAgentExample : public GridAgent<GridAgentExample> {
	private:
		static const MooreRange<VonNeumannGrid<>> range;

	public:
		FPMAS_MOBILITY_RANGE(range);
		FPMAS_PERCEPTION_RANGE(range);

		/**
		 * Agent behavior.
		 */
		void move();
};

FPMAS_DEFAULT_JSON(GridAgentExample);
