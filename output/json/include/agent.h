#include "fpmas/model/model.h"

/**
 * FPMAS Agent example
 */
class Agent : public fpmas::model::AgentBase<Agent> {
	private:
		static fpmas::random::DistributedGenerator<> rd;

		// Agent data
		int count = 0;
		std::vector<std::string> messages;

	public:
		Agent() = default;
		Agent(
				int count,
				const std::vector<std::string>& messages
			 ) : count(count), messages(messages) {
		}

		int getCount() const {return count;}
		std::vector<std::string> getMessages() const {
			return messages;
		}

		/**
		 * Adds a random message to `messages` and increases `count` by 1.
		 */
		void generate_new_message();

		static void to_json(nlohmann::json& j, const Agent* agent);
		static Agent* from_json(const nlohmann::json& j);
};
