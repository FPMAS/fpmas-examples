#include "fpmas/model/model.h"
#include "fpmas/model/serializer.h"

class Agent1 : public fpmas::model::AgentBase<Agent1> {
	public:
		void act() {
			std::cout << "[Agent 1] Agent "
				<< FPMAS_C_STR(this->node()->getId()) << " acts."
				<< std::endl;
		}
};
FPMAS_DEFAULT_JSON(Agent1);

class Agent2 : public fpmas::model::AgentBase<Agent2> {
	public:
		void act() {
			std::cout << "[Agent 2] Agent "
				<< FPMAS_C_STR(this->node()->getId()) << " acts."
				<< std::endl;
		}
};
FPMAS_DEFAULT_JSON(Agent2);

