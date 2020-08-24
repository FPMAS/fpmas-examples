/* include/agents.h */

#include "fpmas/model/model.h"
#include "fpmas/model/serializer.h"

class Agent1 : public fpmas::model::AgentBase<Agent1> {
	public:
		void act() override;
};

FPMAS_DEFAULT_JSON(Agent1)


class Agent2 : public fpmas::model::AgentBase<Agent2> {
	public:
		void act() override;
};

FPMAS_DEFAULT_JSON(Agent2)
