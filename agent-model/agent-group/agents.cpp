#include "agents.h"

void Agent1::behavior_0() {
	std::cout << "[Agent 1] Hello from Agent "
		<< FPMAS_C_STR(this->node()->getId())
		<< std::endl;
}

void Agent1::behavior_1() {
	std::cout << "[Agent 1] Agent "
		<< FPMAS_C_STR(this->node()->getId()) << " acts."
		<< std::endl;
}

void Agent2::behavior_1() {
	std::cout << "[Agent 2] Agent "
		<< FPMAS_C_STR(this->node()->getId()) << " acts."
		<< std::endl;
}
