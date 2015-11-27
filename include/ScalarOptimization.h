#ifndef _SCALAR_OPTIMIZATION_H
#define _SCALAR_OPTIMIZATION_H

#include "Fitness.h"
#include "HillClimbing.h"
#include "Neighborhood.h"
#include "Select.h"

template<unsigned int Size, unsigned int Objective>
class ScalarFintess {

public:
	unsigned int execute(const Instance<Size, Objective>& instance, const Solution<Size>& solution) const {
		float total = 0.f;
		for(unsigned int i=0; i<Objective; i++)
			total += _coefficients[i]*(float)Fitness::unique(instance, solution, i);
		return (unsigned int)total;
	}

	float _coefficients[Objective];

};

template<unsigned int Size, unsigned int Objective>
class ScalarOptimization {

public:
	static void execute(const Instance<Size, Objective>& instance, const Solution<Size>& init_solution, std::vector<Solution<Size>>& list_solution, float delta) {
		ScalarFintess<Size, Objective> fitness;
		Solution<Size> current_solution(init_solution);

		for(float cursor=0.0; cursor <= 1.0f; cursor += delta) {
			fitness._coefficients[0] = cursor;
			_execute<1>(instance, current_solution, fitness, list_solution, delta, 1.0f-cursor);
		}
	}

	template<unsigned int CurrentObjective>
	static typename std::enable_if<(CurrentObjective+1 < Objective)>::type _execute(const Instance<Size, Objective>& instance, Solution<Size>& current_solution, ScalarFintess<Size, Objective>& fitness, std::vector<Solution<Size>>& list_solution, float delta, float remain) {
		for(float cursor=0.0; cursor <= remain; cursor += delta) {
			fitness._coefficients[CurrentObjective] = cursor;
			_execute<CurrentObjective+1>(instance, current_solution, fitness, list_solution, delta, remain-cursor);
		}
	}

	template<unsigned int CurrentObjective>
	static typename std::enable_if<(CurrentObjective+1 >= Objective)>::type _execute(const Instance<Size, Objective>& instance, Solution<Size>& current_solution, ScalarFintess<Size, Objective>& fitness, std::vector<Solution<Size>>& list_solution, float delta, float remain) {
		fitness._coefficients[CurrentObjective] = remain;
		HillClimbing<Size, Objective>::template execute<TwoOpt, SelectFirst, ScalarFintess<Size, Objective>>(instance, current_solution, fitness);

		list_solution.push_back(current_solution);

	}
};

#endif
