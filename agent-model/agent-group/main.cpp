#include "fpmas.h"
#include "agents.h"

using fpmas::synchro::HardSyncMode;

using fpmas::communication::MpiCommunicator;
using fpmas::model::AgentGroup;

FPMAS_JSON_SET_UP(Agent1, Agent2);
FPMAS_DEFINE_GROUPS(G1, G2);

void print_agents(const AgentGroup& group, MpiCommunicator& comm);

int main(int argc, char** argv) {
	FPMAS_REGISTER_AGENT_TYPES(Agent1, Agent2);
	fpmas::init(argc, argv);
	{
		fpmas::model::Model<HardSyncMode> model;

		AgentGroup& group_1 = model.buildGroup(G1);
		AgentGroup& group_2 = model.buildGroup(G2);

		Agent1* a1 = new Agent1;
		Agent2* a2 = new Agent2;
		group_1.add(a1);
		group_1.add(a2);

		print_agents(group_1, model.getMpiCommunicator());
	}
	fpmas::finalize();
}

void print_agents(const AgentGroup& group, MpiCommunicator& comm) {
	for(int rank = 0; rank < comm.getSize(); rank++) {
		FPMAS_ON_PROC(comm, rank) {
			std::cout << "Group " << group.groupId() << " agents on process "
				<< comm.getRank() << ":" << std::endl;
			for(auto agent : group.localAgents()) {
				std::cout << "- ID: " << agent->get()->node()->getId()
					<< ", Type: " << agent->get()->typeId().name()
					<< std::endl;
			}
		}
		comm.barrier();
	}
}
