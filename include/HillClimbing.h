#ifndef _HILL_CLIMBING_H
#define _HILL_CLIMBING_H

#include "ScalarOptimization.h"

template<unsigned int Size, unsigned int Objective>
class HillClimbing {

public:

	template<template<unsigned int> class Neighborhood, template<unsigned int, unsigned int> class Select, typename Fitness>
	static void execute(const Instance<Size, Objective>& instance, Solution<Size>& solution, const Fitness& fitness) {
		Neighborhood<Size> neighborhood;

		neighborhood.selected();

		while(Select<Size, Objective>::execute(instance, solution, neighborhood, fitness))
			neighborhood.selected();
	}
};

#endif
