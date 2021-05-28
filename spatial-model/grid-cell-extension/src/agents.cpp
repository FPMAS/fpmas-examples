#include "agents.h"

void GrowingGridCell::to_json(nlohmann::json &j, const GrowingGridCell *cell) {
	j = cell->value;
}

GrowingGridCell* GrowingGridCell::from_json(const nlohmann::json &j) {
	return new GrowingGridCell(j.get<int>());
}

void GrowingGridCell::grow() {
	std::cout
		<< "Step " << this->model()->runtime().currentDate() << ": "
		<< "Growing " << this->location() << " (value: " << this->value << ")"
		<< std::endl;
	this->value++;
}

void GrowingGridCell::clear() {
	this->value = 0;
}

const VonNeumannRange<VonNeumannGrid<GrowingGridCell>> EatingGridAgent::mobility_range(1);
const VonNeumannRange<VonNeumannGrid<GrowingGridCell>> EatingGridAgent::perception_range(0);

void EatingGridAgent::eat() {
	std::cout
		<< "Step " << this->model()->runtime().currentDate() << ": "
		<< this->node()->getId() << " eats " << this->locationCell()->location() << "."
		<< std::endl;

	auto cell = this->locationCell();
	{
		AcquireGuard acq(cell);
		cell->clear();
	}
	this->moveTo(this->mobilityField().random());
}
