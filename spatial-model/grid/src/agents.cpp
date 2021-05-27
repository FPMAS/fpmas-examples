#include "agents.h"

MooreRange<VonNeumannGrid<>> GridAgentExample::range(1);

void GridAgentExample::move() {
	std::cout
		<< "Agent " << this->node()->getId() << ":" << std::endl
		<< "    Step: " << this->model()->runtime().currentDate() << std::endl
		<< "    Location: " << this->locationCell()->location() << std::endl
		<< "    Perceptions: [ ";
	for(auto agent : this->perceptions())
		std::cout << agent->node()->getId() << " ";
	std::cout << "]" << std::endl;
	
	// Gets GraphCells currently in the agent mobility field
	auto mobility_field = this->mobilityField();

	// Selects a random GridCell from the mobility field
	auto cell = mobility_field.random();

	// Moves to this cell
	this->moveTo(cell);
}
