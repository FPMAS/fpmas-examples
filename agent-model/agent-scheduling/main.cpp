#include "fpmas.h"
#include "agents.h"
#include <thread>
#include <chrono>

using fpmas::synchro::HardSyncMode;

using fpmas::communication::MpiCommunicator;
using fpmas::model::AgentGroup;

FPMAS_JSON_SET_UP(Agent1, Agent2);
FPMAS_DEFINE_GROUPS(G0, G1);

void print_agents(const AgentGroup& group, MpiCommunicator& comm);

class PrintAgentsTask : public fpmas::api::scheduler::Task {
	private:
		AgentGroup& group;
		MpiCommunicator& comm;
	public:
		PrintAgentsTask(AgentGroup& group, MpiCommunicator& comm)
			: group(group), comm(comm) {}

		void run() override {
			print_agents(group, comm);
		}
};

class PrintCurrentTimeStepTask : public fpmas::api::scheduler::Task {
	private:
		fpmas::api::runtime::Runtime& runtime;
		MpiCommunicator& comm;
	public:
		PrintCurrentTimeStepTask(fpmas::api::runtime::Runtime& runtime, MpiCommunicator& comm)
			: runtime(runtime), comm(comm) {}

		void run() override {
			FPMAS_ON_PROC(comm, 0)
				std::cout << std::endl << "== TimeStep: " << runtime.currentDate() << std::endl;
			std::this_thread::sleep_for(std::chrono::duration<double>(.5));
			comm.barrier();
		}
};

int main(int argc, char** argv) {
	FPMAS_REGISTER_AGENT_TYPES(Agent1, Agent2);
	fpmas::init(argc, argv);
	{
		fpmas::model::Model<HardSyncMode> model;

		AgentGroup& group_0 = model.buildGroup(G0);
		AgentGroup& group_1 = model.buildGroup(G1);

		// Adds two Agent1 to group_1 on each process
		group_0.add(new Agent1);
		group_0.add(new Agent1);

		// Adds an Agent1 and an Agent2 to group_2 on each process
		group_1.add(new Agent2);
		group_1.add(new Agent2);

		// Task to print time steps from process 0
		PrintCurrentTimeStepTask print_time_step(model.runtime(), model.getMpiCommunicator());
		// begin_task: void
		// tasks: print_time_step
		// end_task: void
		fpmas::scheduler::Job print_time_step_job({print_time_step});

		// Executed at 0.0, 1.0, 2.0...
		model.scheduler().schedule(0, 1, print_time_step_job);

		// Executed at 0.1
		model.scheduler().schedule(0.1, group_0.job());
		// Executed at 2.1 and 3.1
		model.scheduler().schedule(2.1, 4, 1, group_0.job());
		// Executed at 0.2, 2.2, 4.2...
		model.scheduler().schedule(0.2, 2, group_1.job());

		// Task to print group_0
		PrintAgentsTask print_group_0(group_0, model.getMpiCommunicator());
		// Task to print group_1
		PrintAgentsTask print_group_1(group_1, model.getMpiCommunicator());

		// begin_task: print_group_0
		// tasks: void
		// end_task: print_group_1
		fpmas::scheduler::Job print_groups_job(print_group_0, {}, print_group_1);

		// Executed at 0.3, 1.3, 2.3, ...
		model.scheduler().schedule(0.3, 1, print_groups_job);

		// Runs the model for 4 TimeSteps
		model.runtime().run(4);
	}
	fpmas::finalize();
}

void print_agents(const AgentGroup& group, MpiCommunicator& comm) {
	if(comm.getRank() == 0)
		std::cout << std::endl;
	for(int rank = 0; rank < comm.getSize(); rank++) {
		FPMAS_ON_PROC(comm, rank) {
			std::this_thread::sleep_for(std::chrono::duration<double>(.5));
			std::cout
				<< "Group " << group.groupId() << " agents on process "
				<< comm.getRank() << ":" << std::endl;
			for(auto agent : group.localAgents()) {
				std::cout
					<< "- ID: " << agent->get()->node()->getId()
					<< ", Type: " << agent->get()->typeId().name()
					<< std::endl;
			}
		}
		comm.barrier();
	}
}
