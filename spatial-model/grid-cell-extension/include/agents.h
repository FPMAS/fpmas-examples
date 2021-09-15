#include "fpmas.h"

using namespace fpmas::model;

class GrowingGridCell : public GridCellBase<GrowingGridCell> {
	private:
		int value;

	public:
		// Imports constructors (required)
		using GridCellBase<GrowingGridCell>::GridCellBase;

		/**
		 * Default constructor.
		 */
		GrowingGridCell() : GrowingGridCell(0) {}
		/**
		 * GrowingGridCell constructor.
		 */
		GrowingGridCell(int value) : value(value) {}

		/**
		 * GrowingGridCell behavior.
		 *
		 * Increments internal value by 1.
		 */
		void grow();

		/**
		 * Sets internal value to 0.
		 */
		void clear();

		static void to_json(nlohmann::json& j, const GrowingGridCell* cell);
		static GrowingGridCell* from_json(const nlohmann::json& j);
};

class EatingGridAgent : public GridAgent<EatingGridAgent, GrowingGridCell> {
	private:
		static const VonNeumannRange<VonNeumannGrid<GrowingGridCell>> mobility_range;
		static const VonNeumannRange<VonNeumannGrid<GrowingGridCell>> perception_range;

	public:
		FPMAS_MOBILITY_RANGE(mobility_range);
		FPMAS_PERCEPTION_RANGE(perception_range);

		/**
		 * EatingGridAgent behavior.
		 */
		void eat();
};

FPMAS_DEFAULT_JSON(EatingGridAgent);
