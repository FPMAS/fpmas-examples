/* src/agents.cpp */
#include "agents.h"

void Agent::behavior() {
	std::cout 
		<< "[Step " << this->model()->runtime().currentDate() << "] Agent " << this->node()->getId()
		<< " acts from proc " << this->model()->graph().getMpiCommunicator().getRank()
		<< std::endl;
}

void Agent::to_json(nlohmann::json& j, const Agent* agent) {
	j["c"] = agent->count;
	j["m"] = agent->message;
}

Agent* Agent::from_json(const nlohmann::json& j) {
	return new Agent(
			j.at("c").get<int>(),
			j.at("m").get<std::string>()
			);
}
