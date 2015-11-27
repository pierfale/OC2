#ifndef _FILTER_H
#define _FILTER_H

#include <vector>
#include <algorithm>

#include "Fitness.h"

template<typename Logger>
class FilterFunction {

public:

	template<unsigned int Objective>
	static bool is_dominate(const FitnessPoint<Objective>& point1, const FitnessPoint<Objective>& point2) {
		for(unsigned int i=0; i<Objective; i++) {
			Logger::on_comparaison();
			if(point1._fitness[i] > point2._fitness[i])
				return false;
		}
		return true;
	}

	template<unsigned int Objective>
	static bool dominate(const FitnessPoint<Objective>& point1, const FitnessPoint<Objective>& point2) {
		for(unsigned int i=0; i<Objective; i++) {
			Logger::on_comparaison();
			if(point1._fitness[i] < point2._fitness[i])
				return false;
		}
		return true;
	}
};

template<typename Logger>
class OfflineFilter {

public:
	template<unsigned int Size, unsigned int Objective>
	static void execute(const Instance<Size, Objective>& instance, const std::vector<Solution<Size>>& list_input, std::vector<Solution<Size>>& list_output) {

		for(auto it_solution = std::begin(list_input); it_solution != std::end(list_input); ++it_solution) {
			auto fitness_1 = Fitness::generate(instance, *it_solution);

			if(std::none_of(std::begin(list_input), std::end(list_input), [&](const Solution<Size>& solution) {
							auto fitness_2 = Fitness::generate(instance, solution);

							if(fitness_2 == fitness_1) // discard same object
								return false;
							return FilterFunction<Logger>::is_dominate(fitness_2, fitness_1);
						})) {
				list_output.push_back(*it_solution);
			}
		}
	}
};

template<typename Logger, unsigned int Size, unsigned int Objective>
class OnlineFilter {

public:
	OnlineFilter(const Instance<Size, Objective>& instance) : _instance(instance){

	}

	void add(const Solution<Size>& solution) {
		auto fitness = Fitness::generate(_instance, solution);

		for(auto it_dominate = std::begin(_dominate_list); it_dominate != std::end(_dominate_list); ++it_dominate) {
			auto fitness_dominate = Fitness::generate(_instance, *it_dominate);
			if(fitness != fitness_dominate  && FilterFunction<Logger>::is_dominate(fitness, fitness_dominate)) {
				_dominate_list.erase(it_dominate);
				--it_dominate;
			}
		}

		if(std::none_of(std::begin(_dominate_list), std::end(_dominate_list), [&](const Solution<Size>& solution2) {
						auto fitness2 = Fitness::generate(_instance, solution2);
						if(fitness == fitness2)
							return false;
						return FilterFunction<Logger>::is_dominate(fitness2, fitness);
					})) {
			_dominate_list.push_back(solution);
		}

	}

	std::vector<Solution<Size>>& dominate_list() {
		return _dominate_list;
	}


private:
	const Instance<Size, Objective>& _instance;
	std::vector<Solution<Size>> _dominate_list;
};

#endif
