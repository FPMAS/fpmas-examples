#include "fpmas/model/model.h"
#include "fpmas/model/serializer.h"

class AgentBehavior1 {
	public:
		virtual void behavior_1() = 0;
};

class Agent1 : public fpmas::model::AgentBase<Agent1>, public AgentBehavior1 {
	public:
		void behavior_0();

		void behavior_1() override;
};
FPMAS_DEFAULT_JSON(Agent1);

class Agent2 : public fpmas::model::AgentBase<Agent2>, public AgentBehavior1 {
	public:
		void behavior_1() override;
};
FPMAS_DEFAULT_JSON(Agent2);

