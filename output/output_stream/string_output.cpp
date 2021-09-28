#include "fpmas.h"

FPMAS_JSON_SET_UP()

int main(int argc, char** argv) {
	fpmas::init(argc, argv);
	{
		std::string str = "Hello World";

		fpmas::io::StringOutput out;
		out << str << std::endl << str << std::endl;

		std::cout << out.str();
	}
	fpmas::finalize();
}
