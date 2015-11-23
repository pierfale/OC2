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
	template<unsigned int Objective>
	static void execute(const std::vector<FitnessPoint<Objective>>& list_input, std::vector<FitnessPoint<Objective>>& list_output) {

		for(auto it_point = std::begin(list_input); it_point != std::end(list_input); ++it_point) {

			if(std::none_of(std::begin(list_input), std::end(list_input), [&](const FitnessPoint<Objective>& point) {
							if(point == *it_point) // discard same object
								return false;
							return FilterFunction<Logger>::is_dominate(point, *it_point);
						})) {
				list_output.push_back(*it_point);
			}
		}
	}
};

template<typename Logger, unsigned int Objective>
class OnlineFilter {

public:
	OnlineFilter() {

	}

	void add(const FitnessPoint<Objective>& point) {

		for(auto it_point = std::begin(_dominate_list); it_point != std::end(_dominate_list); ++it_point) {
			if(point != *it_point && FilterFunction<Logger>::is_dominate(point, *it_point)) {
				_dominate_list.erase(it_point);
				--it_point;
			}
		}

		if(std::none_of(std::begin(_dominate_list), std::end(_dominate_list), [&](const FitnessPoint<Objective>& point2) {
						if(point == point2)
							return false;
						return FilterFunction<Logger>::is_dominate(point2, point);
					})) {
			_dominate_list.push_back(point);
		}

	}

	std::vector<FitnessPoint<Objective>>& dominate_list() {
		return _dominate_list;
	}


private:
	std::vector<FitnessPoint<Objective>> _dominate_list;
};

#endif
