#include "fpmas.h"

FPMAS_JSON_SET_UP();

int main(int argc, char** argv) {
	fpmas::init(argc, argv);
	{
		// Example data
		std::size_t index = 0;
		std::vector<std::string> data {"Hey", "Ho"};

		// OutputStream
		fpmas::io::Cout output_stream;

		// Scheduler + runtime
		fpmas::scheduler::Scheduler scheduler;
		fpmas::runtime::Runtime runtime(scheduler);

		// Task used to switch index in {0, 1}
		fpmas::scheduler::detail::LambdaTask switch_index_task(
				[&index] () {index = (index+1)%2;}
				);
		fpmas::scheduler::Job switch_index({switch_index_task});

		// Data Watcher
		fpmas::io::Watcher<std::string> watcher = [&runtime, &data, &index] () {
			return data[index] + " from time step " + std::to_string(runtime.currentDate());
		};

		// An output that fetches data from `watcher` at each dump() and sends
		// it to `output_stream` using the << operator.
		fpmas::io::FormattedOutput<std::string> output(
				output_stream, watcher,
				true // Inserts new lines at each dump
				);

		// Switches index at each time step, from time step 1
		scheduler.schedule(1, 1, switch_index);
		// Performs output at each time step, after switch_index
		scheduler.schedule(0.1, 1, output.job());

		// Runs for 5 time steps
		runtime.run(5);
	}
	fpmas::finalize();
}
