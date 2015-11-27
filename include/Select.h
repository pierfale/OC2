#ifndef _SELECT_H
#define _SELECT_H

#include "Instance.h"
#include "Solution.h"

template <unsigned int Size, unsigned int Objective>
class SelectFirst {

public:
	template<template<unsigned int> class Neighborhood, typename Fitness>
	static bool execute(const Instance<Size, Objective>& input, Solution<Size>& output, Neighborhood<Size>& neighborhood, const Fitness& fitness) {

		unsigned int initial_score = fitness.execute(input, output);
		Solution<Size> initial_output(output);


		do {
			output = initial_output;

			neighborhood.next();

			if(!neighborhood.execute(output)) {
				output = initial_output;
				return false;
			}

		} while(fitness.execute(input, output) >= initial_score);

		return true;
	}
};

template <unsigned int Size, unsigned int Objective>
class SelectBest {

public:
	template<template<unsigned int> class Neighborhood, typename Fitness>
	static bool execute(const Instance<Size, Objective>& input, Solution<Size>& output, Neighborhood<Size>& neighborhood, const Fitness& fitness) {
		Solution<Size> initial_output(output);
		Solution<Size> best_output(output);
		unsigned int best_score = fitness.execute(input, output);
		unsigned int initial_score = best_score;

		while(neighborhood.process(input, output)) {

			unsigned int current_score;
			if((current_score = fitness.execute(input, output)) < best_score) {
				best_output = output;
				best_score = current_score;
			}
			output = initial_output;
		}

		neighborhood.selected();

		output = best_output;

		return best_score < initial_score;
	}
};

#endif
