#ifndef _NEIGHBORHOOD_H
#define _NEIGHBORHOOD_H

#include <algorithm>

#include "Solution.h"

template<unsigned int Size>
class Swap {

public:
	Swap() : _index1(0), _index2(0) {
		incrementIndex();
	}

	void incrementIndex() {
		_index1++;

		if(_index1 == _index2) {
			_index1++;
		}

		if(_index1 >= Size) {
			_index2++;
			_index1 = 0;
		}

		if(_index1 == _index2) {
			_index1++;
		}

		if(_index2 >= Size) {
			_index1 = 0;
			_index2 = 1;
		}
	}

	void rand() {
		_index1 = ::rand()%Size;
		_index2 = ::rand()%Size;

		if(_index1 == _index2) {
			_index2++;
		}

		if(_index2 >= Size) {
			_index2 = 0;
		}
	}

	void execute(Solution<Size>& solution) {
		std::swap(solution._order[_index1], solution._order[_index2]);
	}

private:
	unsigned int _index1;
	unsigned int _index2;

};

#endif
