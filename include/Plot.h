#ifndef _PLOT_H
#define _PLOT_H

#include <fstream>

#include "Filter.h"
#include "PassiveLogger.h"

class PlotFitness {

public:
	template<unsigned int Size, unsigned int Objective>
	static void execute(const Instance<Size, Objective>& instance, const std::vector<Solution<Size>>& list_input, const std::string& file_output) {

		std::vector<Solution<Size>> list_input_dominate;
		OfflineFilter<PassiveLogger>::execute(instance, list_input, list_input_dominate);

		std::vector<FitnessPoint<Objective>> list_fitness_dominate;
		for(auto it_solution = std::begin(list_input_dominate); it_solution != std::end(list_input_dominate); ++it_solution)
			list_fitness_dominate.push_back(Fitness::generate(instance, *it_solution));

		std::ofstream file(file_output, std::ios::trunc | std::ios::out);

		if(file) {
			for(auto it_solution = std::begin(list_input); it_solution != std::end(list_input); ++it_solution) {
				auto it_fitness = Fitness::generate(instance, *it_solution);
				for(unsigned int i=0; i<Objective; i++)
					file << it_fitness._fitness[i] << "\t";
				file << (std::find(std::begin(list_fitness_dominate), std::end(list_fitness_dominate), it_fitness) != std::end(list_fitness_dominate) ? 1 : 0) << std::endl;
			}

			file.close();
		}
		else
			throw std::runtime_error("Unable to open "+file_output);
	}

};

#endif
