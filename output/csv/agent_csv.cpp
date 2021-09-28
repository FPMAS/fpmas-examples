#include "fpmas.h"
#include "agent.h"

FPMAS_JSON_SET_UP(Agent);

int main(int argc, char** argv) {
	fpmas::init(argc, argv);
	{
		fpmas::model::Model<fpmas::synchro::GhostMode> model;
		fpmas::model::Behavior<Agent> switch_group(&Agent::switchGroup);
		auto& group_0 = model.buildGroup(GROUP_0, switch_group);
		auto& group_1 = model.buildGroup(GROUP_1, switch_group);

		// Builds 40 agents in total in group_0 (distributed process)
		build_agents(model, group_0);
		// Builds 40 agents in total in group_1 (distributed process)
		build_agents(model, group_1);

		// Opens a file on each process
		fpmas::io::FileOutput out("output.%r.csv", model.getMpiCommunicator().getRank());
		// Defines CSV output
		fpmas::io::CsvOutput<fpmas::scheduler::TimeStep, std::size_t, std::size_t, int>
			csv_output(out,
					{"time", [&model] () {
						// Current time step
						return fpmas::scheduler::time_step(model.runtime().currentDate());
						}},
					{"local_group_0", [&group_0] () {
						// LOCAL Agent count in group_0
						return group_0.localAgents().size();
						}},
					{"local_group_1", [&group_1] () {
						// LOCAL Agent count in group_1
						return group_1.localAgents().size();
						}},
					{"local_count", [&group_0, &group_1] () {
						// Sum of Agent::getCount() for all LOCAL agents
						int count = 0;
						for(auto agent : fpmas::utils::ptr_wrapper_cast<Agent>(
									group_0.localAgents()))
							count+=agent->getCount();
						for(auto agent : fpmas::utils::ptr_wrapper_cast<Agent>(
									group_1.localAgents()))
							count+=agent->getCount();
						return count;
					}}
					);

		// Schedules group_0, group_1, and CSV output at each time step
		model.scheduler().schedule(0.1, 1, group_0.jobs());
		model.scheduler().schedule(0.2, 1, group_1.jobs());
		model.scheduler().schedule(0.3, 1, csv_output.job());

		// Executes 10 time steps
		model.runtime().run(10);
	}
	fpmas::finalize();
}
