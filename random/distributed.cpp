#include "fpmas.h"

FPMAS_JSON_SET_UP();

int main(int argc, char** argv) {
	fpmas::init(argc, argv);
	{
		std::cout << "== Distributed Generator (default seed) ==" << std::endl;
		fpmas::random::DistributedGenerator<> dist_rd;
		for(int i = 0; i < 10; i++)
			std::cout << dist_rd() << std::endl;

		std::cout <<  "== Distributed Generator (seed: 8) ==" << std::endl;
		dist_rd = fpmas::random::DistributedGenerator<>(8);
		for(int i = 0; i < 10; i++)
			std::cout << dist_rd() << std::endl;

		std::cout <<  "== Distributed Generator Reproducibility (seed: 8) ==" << std::endl;
		dist_rd = fpmas::random::DistributedGenerator<>(8);
		for(int i = 0; i < 10; i++)
			std::cout << dist_rd() << std::endl;
	}
	fpmas::finalize();
}
