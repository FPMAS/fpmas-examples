/* include/agents.h */

#include "fpmas/model/model.h"
#include "fpmas/model/serializer.h"

class Agent1 : public fpmas::model::AgentBase<Agent1> {
	private:
		int count;
		std::string message;
	public:
		Agent1(int count, std::string message)
			: count(count), message(message) {}

		static void to_json(nlohmann::json& j, const Agent1* agent); 
		static Agent1* from_json(const nlohmann::json& j); 

		void act() override;
};

class Agent2 : public fpmas::model::AgentBase<Agent2> {
	public:
		void act() override;
};

FPMAS_DEFAULT_JSON(Agent2)
