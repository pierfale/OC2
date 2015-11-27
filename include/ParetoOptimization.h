#ifndef _PARETO_OPTIMIZATION_H
#define _PARETO_OPTIMIZATION_H

#include "Instance.h"
#include "Solution.h"
#include "Filter.h"
#include "PassiveLogger.h"

template<unsigned int Size, unsigned int Objective>
class ParetoOptimization {

public:
	static void execute(const Instance<Size, Objective>& instance, const std::vector<Solution<Size>>& init_solution, std::vector<Solution<Size>>& list_solution) {

		std::vector<Solution<Size>> dominate_list;


		OfflineFilter<PassiveLogger>::execute(instance, init_solution, dominate_list);

		list_solution = dominate_list;
	}
};

#endif
