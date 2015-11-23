#include <iostream>

#include "ParserTSP.h"
#include "Fitness.h"
#include "Neighborhood.h"
#include "Filter.h"
#include "Plot.h"
#include "BenchLogger.h"
#include "ScalarOptimization.h"

#define SIZE 100
#define OBJECTIVE 2

int main() {

	Instance<SIZE, OBJECTIVE> instance;
	ParserTSP::execute(instance, "data/randomA100.tsp", "data/randomB100.tsp", "data/randomC100.tsp");

	std::vector<FitnessPoint<OBJECTIVE>> fitness_list;

	for(unsigned int i = 0; i < 5000; i++) {
		Solution<SIZE> solution;

		solution.initialize();

		Swap<SIZE> permutation;
		permutation.rand();
		permutation.execute(solution);

		ScalarOptimization<SIZE, OBJECTIVE>::execute(instance, solution);

		fitness_list.push_back(Fitness::execute(instance, solution));
	}
/*
	std::vector<FitnessPoint<OBJECTIVE>> dominate_fitness_list;

	OfflineFilter<BenchLogger>::execute(fitness_list, dominate_fitness_list);

	std::cout << "Dominate : " << dominate_fitness_list.size() << std::endl;

	for(auto it_point = std::begin(dominate_fitness_list); it_point != std::end(dominate_fitness_list); ++it_point) {
		std::cout << it_point->_fitness[0] << "-" << it_point->_fitness[1] << std::endl;
	}

	std::cout << "Comparaison : " << BenchLogger::comparaison_number() << std::endl;

	PlotFitness::execute(fitness_list, "fitness_file.data");

*/
/*
	OnlineFilter<OBJECTIVE> filter;

	for(auto it_point = std::begin(fitness_list); it_point != std::end(fitness_list); ++it_point) {
		filter.add(*it_point);
	}

	std::cout << "Dominate : " << filter.dominate_list().size() << std::endl;

	for(auto it_point = std::begin(filter.dominate_list()); it_point != std::end(filter.dominate_list()); ++it_point) {
		std::cout << it_point->_fitness[0] << "-" << it_point->_fitness[1] << std::endl;
	}*/
}
