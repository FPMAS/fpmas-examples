#include "fpmas.h"

FPMAS_DEFAULT_JSON_SET_UP()

int main(int argc, char** argv) {
	fpmas::init(argc, argv);
	{
		std::string str = "Hello World";

		// Opens the file in `out` mode (overrides previous content)
		fpmas::io::FileOutput out("file.txt");
		out << str << std::endl;

		// Closes `file.txt` and reopens it in `app` mode, so that the previous
		// content is not overriden
		out = {"file.txt", std::ios::app};
		out << "hey" << std::endl;
	}
	fpmas::finalize();
}
