#include "agents.h"

void Agent1::action() {
	std::cout << "[Agent 1] Agent "
		<< FPMAS_C_STR(this->node()->getId()) << " acts."
		<< std::endl;
}

void Agent1::hello() {
	std::cout << "[Agent 1] Goodbye from Agent "
		<< FPMAS_C_STR(this->node()->getId())
		<< std::endl;
}

void Agent2::action() {
	std::cout << "[Agent 2] Agent "
		<< FPMAS_C_STR(this->node()->getId()) << " acts."
		<< std::endl;
}
