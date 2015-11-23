#ifndef _PLOT_H
#define _PLOT_H

#include <fstream>

#include "Filter.h"
#include "PassiveLogger.h"

class PlotFitness {

public:
	template<unsigned int Objective>
	static void execute(const std::vector<FitnessPoint<Objective>>& list_input, const std::string& file_output) {

		std::vector<FitnessPoint<Objective>> list_input_dominate;
		OfflineFilter<PassiveLogger>::execute(list_input, list_input_dominate);

		std::ofstream file(file_output, std::ios::trunc | std::ios::out);

		if(file) {
			for(auto it_point = std::begin(list_input); it_point != std::end(list_input); ++it_point) {
				for(unsigned int i=0; i<Objective; i++)
					file << it_point->_fitness[i] << "\t";
				file << (std::find(std::begin(list_input_dominate), std::end(list_input_dominate), *it_point) != std::end(list_input_dominate) ? 1 : 0) << std::endl;
			}

			file.close();
		}
		else
			throw std::runtime_error("Unable to open "+file_output);
	}

};

#endif
