#include "agent_view.h"

AgentView::AgentView(const Agent* agent) :
	id(agent->node()->getId()),
	type_name(typeid(Agent).name()),
	count(agent->getCount()),
	messages(agent->getMessages()) {
		for(auto agent : agent->outNeighbors<Agent>(AGENT_CONTACT))
			contacts.push_back(agent->node()->getId());
	}

namespace nlohmann {
	void adl_serializer<AgentView>::to_json(json &j, const AgentView &agent_view) {
		j["id"] = agent_view.id;
		j["type"] = agent_view.type_name;
		j["count"] = agent_view.count;
		j["messages"] = agent_view.messages;
		j["contacts"] = agent_view.contacts;
	}
}
