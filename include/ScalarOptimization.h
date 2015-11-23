#ifndef _SCALAR_OPTIMIZATION_H
#define _SCALAR_OPTIMIZATION_H

#include "Fitness.h"
#include "HillClimbing.h"
#include "Neighborhood.h"

template<unsigned int Size, unsigned int Objective>
class ScalarFintess {

public:
	unsigned int execute(Instance<Size, Objective>& instance, Solution<Size>& solution) const {
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
	static void execute(Instance<Size, Objective>& instance, Solution<Size>& solution) {
		ScalarFintess<Size, Objective> fitness;

		for(unsigned int i=0; i<Objective; i++)
			fitness._coefficients[i] = 0.5;

		HillClimbing<TwoOpt, First, ScalarFintess<Size, Objective>>::execute(instance, solution, fitness);



		std::cout << ScalarFintess::execute(instance, solution, coefficients) << std::endl;
	}
};

#endif
