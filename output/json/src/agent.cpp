#include "agent.h"

fpmas::random::DistributedGenerator<> Agent::rd;

void Agent::generate_new_message() {
	fpmas::random::UniformIntDistribution<int> rd_message(-1000, 1000);
	count++;
	messages.push_back(std::to_string(rd_message(rd)));
}

void Agent::to_json(nlohmann::json& j, const Agent* agent) {
	j["count"] = agent->count;
	j["messages"] = agent->messages;
}

Agent* Agent::from_json(const nlohmann::json& j) {
	return new Agent(
			j.at("count").get<int>(),
			j.at("messages").get<std::vector<std::string>>()
			);
}
