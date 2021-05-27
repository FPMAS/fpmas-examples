#include "fpmas.h"

using namespace fpmas::model;

class GridAgentExample : public GridAgent<GridAgentExample> {
	private:
		static MooreRange<VonNeumannGrid<>> range;

	public:
		GridAgentExample() : GridAgent<GridAgentExample>(range, range) {}

		/**
		 * Agent behavior.
		 */
		void move();
};

FPMAS_DEFAULT_JSON(GridAgentExample);
