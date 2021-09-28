#include "fpmas/model/model.h"

FPMAS_DEFINE_GROUPS(GROUP_0, GROUP_1);

class Agent : public fpmas::model::AgentBase<Agent> {
	private:
		static fpmas::random::DistributedGenerator<> gen;
		static fpmas::random::BernoulliDistribution bernoulli;

		int count;

	public:
		Agent() = default;
		Agent(int count) : count(count) {}

		int getCount() const {return count;}

		void switchGroup();

		static void to_json(nlohmann::json& j, const Agent* agent);
		static Agent* from_json(const nlohmann::json& j);
};

/**
 * Builds a **total** of 40 agents (whatever the current process count is) in
 * the specified group.
 */
void build_agents(fpmas::api::model::Model& model, fpmas::api::model::AgentGroup& group);
