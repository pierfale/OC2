#include <iostream>

#include "ParserTSP.h"
#include "Fitness.h"
#include "Neighborhood.h"
#include "Filter.h"
#include "Plot.h"
#include "BenchLogger.h"
#include "ScalarOptimization.h"
#include "ParetoOptimization.h"

#define SIZE 100
#define OBJECTIVE 3

int main() {

	Instance<SIZE, OBJECTIVE> instance;
	ParserTSP::execute(instance, "data/randomA100.tsp", "data/randomB100.tsp", "data/randomC100.tsp");
/*
	std::vector<Solution<SIZE>> init_solution;

	for(unsigned int i = 0; i < 5000; i++) {
		Solution<SIZE> solution;

		solution.initialize();

		Swap<SIZE> permutation;
		permutation.rand();
		permutation.execute(solution);

		init_solution.push_back(solution);
	}
*/
/*
	std::vector<Solution<SIZE>> solution_list;
	Solution<SIZE> solution;

	solution.initialize();

	Swap<SIZE> permutation;
	permutation.rand();
	permutation.execute(solution);
	ScalarOptimization<SIZE, OBJECTIVE>::execute(instance, solution, solution_list, 0.1f);

	for(auto& solution_item : solution_list)
		fitness_list.push_back(Fitness::execute(instance, solution_item));

	PlotFitness::execute(fitness_list, "fitness_file.data");
*/


	std::vector<Solution<SIZE>> solution_list;
	std::vector<Solution<SIZE>> init_solution;
	std::vector<FitnessPoint<OBJECTIVE>> fitness_list;

	for(unsigned int i = 0; i < 5000; i++) {
		Solution<SIZE> solution;
		solution.initialize();

		Swap<SIZE> permutation;
		permutation.rand();
		permutation.execute(solution);
		init_solution.push_back(solution);
	}
	ParetoOptimization<SIZE, OBJECTIVE>::execute(instance, init_solution, solution_list);

	for(auto& solution_item : solution_list)
		fitness_list.push_back(Fitness::generate(instance, solution_item));

	PlotFitness::execute(instance, init_solution, "fitness_file.data");

/*
	std::vector<Solution<SIZE>> dominate_solution_list;

	OfflineFilter<BenchLogger>::execute(instance, init_solution, dominate_solution_list);

	std::cout << "Dominate : " << dominate_solution_list.size() << std::endl;
	std::cout << "Comparaison : " << BenchLogger::comparaison_number() << std::endl;

	PlotFitness::execute(instance, init_solution, "fitness_file.data");
*/

/*
	OnlineFilter<BenchLogger, SIZE, OBJECTIVE> filter(instance);

	for(auto it_point = std::begin(init_solution); it_point != std::end(init_solution); ++it_point) {
		filter.add(*it_point);
	}

	std::cout << "Dominate : " << filter.dominate_list().size() << std::endl;
	*/
}
