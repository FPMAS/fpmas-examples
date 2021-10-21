#include "fpmas.h"

FPMAS_DEFAULT_JSON_SET_UP();

int main(int argc, char** argv) {
	fpmas::init(argc, argv);
	{
		// Observed data
		int data = 2;

		// Watcher definition
		fpmas::api::io::Watcher<int> watcher([&data] () {return data;});

		std::cout << "Current data value: " << watcher() << std::endl;

		// Modifies the original data
		data = 10;

		std::cout << "Current data value: " << watcher() << std::endl;
	}
	fpmas::finalize();
}
