#include "fpmas.h"

FPMAS_JSON_SET_UP();

int main(int argc, char** argv) {
	fpmas::init(argc, argv);
	{
		// Initializes some data
		std::vector<int> data;
		for(int i = 0; i < 10; i++)
			data.push_back(i);

		// OutputStream
		fpmas::io::Cout out;

		// Json output
		fpmas::io::JsonOutput<std::vector<int>> json_output(
				out, // Reference to output stream
				[&data] () {return data;} // Watcher of `data`
				);

		// Dumps json to std::cout
		json_output.dump();
		out << std::endl;

		// Modifies `data`
		for(auto& item : data)
			item += 2;

		// Dumps updated json data to std::cout
		json_output.dump();
		out << std::endl;
	}
	fpmas::finalize();
}
