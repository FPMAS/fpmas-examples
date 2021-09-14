#include "agents.h"

void Agent1::behavior_0() {
	std::cout << "[Agent1] Agent "
		<< FPMAS_C_STR(this->node()->getId())
		<< " executes behavior_0()" << std::endl;
}

void Agent1::behavior_1() {
	std::cout << "[Agent1] Agent "
		<< FPMAS_C_STR(this->node()->getId())
		<< " executes behavior_1()" << std::endl;
}

void Agent2::behavior_1() {
	std::cout << "[Agent2] Agent "
		<< FPMAS_C_STR(this->node()->getId())
		<< " executes behavior_1()" << std::endl;
}
