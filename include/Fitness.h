#ifndef _FITNESS_H
#define _FITNESS_H

#include "Instance.h"
#include "Solution.h"

template<unsigned int Objective>
class FitnessPoint {

public:
	FitnessPoint() {

	}

	bool operator==(const FitnessPoint& that) const {
		for(unsigned int i=0; i<Objective; i++)
			if(_fitness[i] != that._fitness[i])
				return false;
		return true;
	}

	bool operator!=(const FitnessPoint& that) const {
		return !operator==(that);
	}

	unsigned int _fitness[Objective];
};

class Fitness {

public:
	template<unsigned int Size, unsigned int Objective>
	static FitnessPoint<Objective> execute(const Instance<Size, Objective>& instance, const Solution<Size>& solution)  {
		FitnessPoint<Objective> fitness;
		for(unsigned int i=0; i<Objective; i++) {
			fitness._fitness[i] = unique(instance, solution, i);
		}
		return fitness;

	}

	template<unsigned int Size, unsigned int Objective>
	static unsigned int unique(const Instance<Size, Objective>& instance, const Solution<Size>& solution, unsigned int current_objective)  {
		unsigned int total = 0;
		for(unsigned int i=0; i<Size; i++) {
			total += instance._cost[current_objective][solution._order[i]][solution._order[(i+1)%Size]];
		}

		return total;
	}
};

#endif
