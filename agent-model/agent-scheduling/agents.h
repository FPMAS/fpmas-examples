#include "fpmas/model/model.h"
#include "fpmas/model/serializer.h"

class AgentBase {
	public:
		virtual void action() = 0;
};

class Agent1 : public fpmas::model::AgentBase<Agent1>, public AgentBase {
	public:
		void action() override {
			std::cout << "[Agent 1] Agent "
				<< FPMAS_C_STR(this->node()->getId()) << " acts."
				<< std::endl;
		}

		void hello() {
			std::cout << "[Agent 1] Hello from Agent "
				<< FPMAS_C_STR(this->node()->getId())
				<< std::endl;
		}
};
FPMAS_DEFAULT_JSON(Agent1);

class Agent2 : public fpmas::model::AgentBase<Agent2>, public AgentBase {
	public:
		void action() override {
			std::cout << "[Agent 2] Agent "
				<< FPMAS_C_STR(this->node()->getId()) << " acts."
				<< std::endl;
		}
};
FPMAS_DEFAULT_JSON(Agent2);
