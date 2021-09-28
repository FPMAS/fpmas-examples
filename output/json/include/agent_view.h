#include "agent.h"

FPMAS_DEFINE_LAYERS(AGENT_CONTACT);

struct AgentView {
	// Agent id
	DistributedId id;

	// Agent type name
	std::string type_name;

	// Regular Agent data fields
	int count;
	std::vector<std::string> messages;

	// Outgoing neighbors of the Agent on the AGENT_CONTACT layer
	std::vector<DistributedId> contacts;

	AgentView(const Agent* agent);
};

namespace nlohmann {
	template<>
		struct adl_serializer<AgentView> {
			// Only the to_json method is required
			static void to_json(json& j, const AgentView& agent_view);
		};
}
