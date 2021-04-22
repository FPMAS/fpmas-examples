#include "fpmas/model/model.h"
#include "fpmas/model/serializer.h"

class AgentBase {
	public:
		virtual void action() = 0;
};

class Agent1 : public fpmas::model::AgentBase<Agent1>, public AgentBase {
	public:
		void action() override;

		void hello();
};
FPMAS_DEFAULT_JSON(Agent1);

class Agent2 : public fpmas::model::AgentBase<Agent2>, public AgentBase {
	public:
		void action() override;
};
FPMAS_DEFAULT_JSON(Agent2);

