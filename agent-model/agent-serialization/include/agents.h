/* include/agents.h */

#include "fpmas/model/model.h"
#include "fpmas/model/serializer.h"

class Agent : public fpmas::model::AgentBase<Agent> {
	private:
		int count;
		std::string message;
	public:
		Agent(int count, std::string message)
			: count(count), message(message) {}

		static void to_json(nlohmann::json& j, const Agent* agent); 
		static Agent* from_json(const nlohmann::json& j); 

		void behavior();
};
