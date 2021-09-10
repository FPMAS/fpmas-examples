/* src/agents.cpp */
#include "agents.h"

void Agent::behavior() {
	std::cout 
		<< "[Step " << this->model()->runtime().currentDate() << "] Agent " << this->node()->getId()
		<< " acts from proc " << this->model()->graph().getMpiCommunicator().getRank()
		<< std::endl;
}
