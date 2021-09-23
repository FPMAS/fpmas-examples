#include "fpmas.h"

FPMAS_JSON_SET_UP();

int main(int argc, char** argv) {
	fpmas::init(argc, argv);
	{
		std::cout << "== Sequential Generator (default seed) ==" << std::endl;
		fpmas::random::mt19937_64 rd;
		for(int i = 0; i < 10; i++)
			std::cout << rd() << std::endl;

		std::cout <<  "== Sequential Generator (seed: 8) ==" << std::endl;
		rd = fpmas::random::mt19937_64(8);
		for(int i = 0; i < 10; i++)
			std::cout << rd() << std::endl;

		std::cout <<  "== Sequential Generator Reproducibility (seed: 8) ==" << std::endl;
		rd = fpmas::random::mt19937_64(8);
		for(int i = 0; i < 10; i++)
			std::cout << rd() << std::endl;
	}
	fpmas::finalize();
}
