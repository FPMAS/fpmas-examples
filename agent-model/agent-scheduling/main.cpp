#include "fpmas.h"
#include "agents.h"
#include <thread>
#include <chrono>

using fpmas::synchro::HardSyncMode;

using fpmas::communication::MpiCommunicator;
using fpmas::model::AgentGroup;
using fpmas::model::Behavior;

FPMAS_JSON_SET_UP(Agent1, Agent2);
FPMAS_DEFINE_GROUPS(G0, G1);

void print_agents(const AgentGroup& group);

Behavior<AgentBase> action_behavior {&AgentBase::action};
Behavior<Agent1> hello_behavior {&Agent1::hello};

int main(int argc, char** argv) {
	FPMAS_REGISTER_AGENT_TYPES(Agent1, Agent2);
	fpmas::init(argc, argv);
	{
		fpmas::model::Model<HardSyncMode> model;

		AgentGroup& group_0 = model.buildGroup(G0, action_behavior);
		AgentGroup& group_1 = model.buildGroup(G1, hello_behavior);

		// Adds an Agent1 and an Agent2 to group_0 on each process
		group_0.add(new Agent1);
		group_0.add(new Agent2);

		// Adds two Agent1 to group_1 on each process
		group_1.add(new Agent1);
		group_1.add(new Agent1);

		// Task to print time steps from process 0
		fpmas::scheduler::detail::LambdaTask print_time_step([&model] () {
				FPMAS_ON_PROC(model.getMpiCommunicator(), 0)
					std::cout << std::endl << "== TimeStep: " << model.runtime().currentDate() << std::endl;
				std::this_thread::sleep_for(std::chrono::duration<double>(.5));
				model.getMpiCommunicator().barrier();
				}
			);

		// tasks: print_time_step
		fpmas::scheduler::Job print_time_step_job({print_time_step});

		// Executed at 0.0, 1.0, 2.0...
		model.scheduler().schedule(0, 1, print_time_step_job);

		// Executed at 0.1
		model.scheduler().schedule(0.1, group_0.jobs());
		// Executed at 2.1 and 3.1
		model.scheduler().schedule(2.1, 4, 1, group_0.jobs());
		// Executed at 0.2, 2.2, 4.2...
		model.scheduler().schedule(0.2, 2, group_1.jobs());

		// Task to print group_0
		fpmas::scheduler::detail::LambdaTask print_group_0([&group_0, &model] () {
				print_agents(group_0);
				});
		// Task to print group_1
		fpmas::scheduler::detail::LambdaTask print_group_1([&group_1, &model] () {
				print_agents(group_1);
				});

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

void print_agents(const AgentGroup& group) {
	auto& comm = fpmas::communication::WORLD;
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
					<< "- ID: " << agent->node()->getId()
					<< ", Type: " << agent->typeId().name()
					<< std::endl;
			}
		}
		comm.barrier();
	}
}
