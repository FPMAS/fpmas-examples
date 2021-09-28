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

		// Opens a file on each process. The file is open once, when the first
		// write is performed. Since output is performed only on process 0,
		// there is no concurrency issues and the file is opened only on
		// process 0.
		fpmas::io::FileOutput out("output.csv");

		// A Watcher used to sum Agent::getCount() on all LOCAL agents
		fpmas::io::Watcher<int> local_count = [&group_0, &group_1] () {
			int count = 0;
			for(auto agent : fpmas::utils::ptr_wrapper_cast<Agent>(
						group_0.localAgents()))
				count+=agent->getCount();
			for(auto agent : fpmas::utils::ptr_wrapper_cast<Agent>(
						group_1.localAgents()))
				count+=agent->getCount();
			return count;
		};

		using fpmas::io::Local;
		using fpmas::io::Reduce;

		// Defines CSV output
		fpmas::io::DistributedCsvOutput<
			Local<fpmas::scheduler::TimeStep>, // Time step (local field)
			Reduce<std::size_t>, // Agent count in group_0
			Reduce<std::size_t>, // Agent count in group_1
			Reduce<int>, // Total Agent::getCount()
			Reduce<int, fpmas::utils::Min<int>>, // Min Agent::getCount() local sum
			Reduce<int, fpmas::utils::Max<int>> // Max Agent::getCount() local sum
		> csv_output(model.getMpiCommunicator(), 0 /* root process */, out,
					{"time", [&model] () {
						// Current time step
						return fpmas::scheduler::time_step(model.runtime().currentDate());
						}},
					{"total_group_0", [&group_0] () {
						// LOCAL Agent count in group_0
						return group_0.localAgents().size();
						}},
					{"total_group_1", [&group_1] () {
						// LOCAL Agent count in group_1
						return group_1.localAgents().size();
						}},
					{"total_count", local_count},
					{"min_count", local_count},
					{"max_count", local_count}
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
