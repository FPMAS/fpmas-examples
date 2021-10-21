#include "fpmas.h"

FPMAS_DEFAULT_JSON_SET_UP();

int main(int argc, char** argv) {
	fpmas::init(argc, argv);
	{
		fpmas::random::mt19937_64 rd;
		fpmas::random::DistributedGenerator<> dist_rd;

		fpmas::random::UniformIntDistribution<> int_distribution(0, 10);

		std::cout << "== Uniform Int Distribution (sequential) ==" << std::endl;
		for(int i = 0; i < 10; i++)
			std::cout << int_distribution(rd) << std::endl;

		std::cout << "== Uniform Int Distribution (distributed) ==" << std::endl;
		for(int i = 0; i < 10; i++)
			std::cout << int_distribution(dist_rd) << std::endl;

		fpmas::random::PoissonDistribution<> poisson_distribution(5);

		std::cout <<  "== Poisson Distribution (distributed) ==" << std::endl;
		for(int i = 0; i < 10; i++)
			std::cout << poisson_distribution(dist_rd) << std::endl;
	}
	fpmas::finalize();
}
