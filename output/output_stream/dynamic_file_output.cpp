#include "fpmas.h"

FPMAS_JSON_SET_UP()

int main(int argc, char** argv) {
	fpmas::init(argc, argv);
	{
		std::string str = "Hello World";

		fpmas::scheduler::Scheduler scheduler;
		fpmas::runtime::Runtime runtime(scheduler);

		fpmas::io::DynamicFileOutput out(
				"file.%r.%t.txt",
				fpmas::communication::WORLD,
				runtime
				);

		// Writes data to "file.[rank].0.txt"
		runtime.setCurrentDate(0);
		out << str << std::endl;

		// Writes data to "file.[rank].12.txt"
		runtime.setCurrentDate(12);
		out << str << std::endl;
	}
	fpmas::finalize();
}
