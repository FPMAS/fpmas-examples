#include "fpmas.h"

FPMAS_JSON_SET_UP();


static fpmas::random::DistributedGenerator<> gen;
static std::vector<std::string> random_messages {
	"hello", "hey", "ho", "FPMAS", "null"
};

void generate_random_data(int& count, std::string& message, float& weight) {
	fpmas::random::BinomialDistribution<> rd_count(10, 0.4);
	fpmas::random::UniformIntDistribution<std::size_t> rd_message(
			0, random_messages.size()-1);
	fpmas::random::NormalDistribution<> rd_weight(120, 40);

	count = rd_count(gen);
	message = random_messages[rd_message(gen)];
	weight = rd_weight(gen);
}

int main(int argc, char** argv) {
	fpmas::init(argc, argv);
	{
		// Example data
		std::size_t index = 0;
		int count;
		std::string message;
		float weight;

		// A distinct static file is opened on each process
		fpmas::io::FileOutput out(
				"output.%r.csv", // %r is replace by rank
				fpmas::communication::WORLD.getRank() // current process rank
				);

		// CSV output definition
		fpmas::io::CsvOutput<std::size_t, int, std::string, float> csv_output(
				// Output stream
				out,
				// CSV fields + Watchers definition
				{"index", [&index] () {return index;}},
				{"count", [&count] () {return count;}},
				{"message", [&message] () {return message;}},
				{"weight", [&weight] () {return weight;}}
				);

		// A task to increase index by 1 and generate random data
		fpmas::scheduler::detail::LambdaTask increase_index_task(
				[&index, &count, &message, &weight] () {
					index++;
					generate_random_data(count, message, weight);
				}
				);
		fpmas::scheduler::Job increase_index({increase_index_task});

		// FPMAS scheduler and runtime
		fpmas::scheduler::Scheduler scheduler;
		fpmas::runtime::Runtime runtime(scheduler);

		// Schedules data update + csv output at each time step (period 1)
		scheduler.schedule(0, 1, increase_index);
		scheduler.schedule(0.1, 1, csv_output.job());

		// Runs for 5 time steps
		runtime.run(5);
	}
	fpmas::finalize();
}
