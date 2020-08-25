/* src/agents.cpp */
#include "agents.h"

void Agent1::act() {
	std::cout 
		<< "[Agent1][Step " << this->model()->runtime().currentDate() << "] Agent " << this->node()->getId()
		<< " acts from proc " << this->model()->graph().getMpiCommunicator().getRank()
		<< std::endl;
}

void Agent1::to_json(nlohmann::json& j, const Agent1* agent) {
	j["c"] = agent->count;
	j["m"] = agent->message;
}

Agent1* Agent1::from_json(const nlohmann::json& j) {
	return new Agent1(
			j.at("c").get<int>(),
			j.at("m").get<std::string>()
			);
}

void Agent2::act() {
	std::cout
		<< "[Agent2][Step " << this->model()->runtime().currentDate() << "] Agent " << this->node()->getId()
		<< " acts from proc " << this->model()->graph().getMpiCommunicator().getRank()
		<< std::endl;
}
