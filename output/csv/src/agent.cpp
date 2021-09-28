#include "agent.h"

fpmas::random::DistributedGenerator<> Agent::gen;
fpmas::random::BernoulliDistribution Agent::bernoulli(0.5);

void Agent::switchGroup() {
	if(bernoulli(gen)) {
		count++;
		// Changes group with a 50% probability
		if(fpmas::model::is_agent_in_group(this, GROUP_0)) {
			// Moves from GROUP_0 to GROUP_1
			this->model()->getGroup(GROUP_1).add(this);
			this->model()->getGroup(GROUP_0).remove(this);
		} else {
			// Moves from GROUP_1 to GROUP_0
			this->model()->getGroup(GROUP_0).add(this);
			this->model()->getGroup(GROUP_1).remove(this);
		}
	}
}

void Agent::to_json(nlohmann::json &j, const Agent *agent) {
	j = agent->count;
}

Agent* Agent::from_json(const nlohmann::json &j) {
	return new Agent(j.get<int>());
}

void build_agents(fpmas::api::model::Model& model, fpmas::api::model::AgentGroup& group) {
	fpmas::model::DistributedAgentNodeBuilder agent_node_builder(
			group,
			40,
			[] () {return new Agent;},
			model.getMpiCommunicator()
			);
	while(agent_node_builder.localNodeCount() != 0)
		agent_node_builder.buildNode(model.graph());


}

