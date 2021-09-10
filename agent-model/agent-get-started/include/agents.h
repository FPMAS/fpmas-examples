/* include/agents.h */

#include "fpmas/model/model.h"
#include "fpmas/model/serializer.h"

class Agent : public fpmas::model::AgentBase<Agent> {
	public:
		void behavior();
};

FPMAS_DEFAULT_JSON(Agent)
