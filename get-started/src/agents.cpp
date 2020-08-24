/* src/agents.cpp */
#include "agents.h"

void Agent1::act() {
	std::cout 
		<< "[Agent1][Step " << this->model()->runtime().currentDate() << "] Agent " << this->node()->getId()
		<< " acts from proc " << this->model()->graph().getMpiCommunicator().getRank()
		<< std::endl;
}

void Agent2::act() {
	std::cout
		<< "[Agent2][Step " << this->model()->runtime().currentDate() << "] Agent " << this->node()->getId()
		<< " acts from proc " << this->model()->graph().getMpiCommunicator().getRank()
		<< std::endl;
}
