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


template<unsigned int Size>
class TwoOpt {

public:
	TwoOpt() : _index1(0), _index2(0) {
		next();
	}

	void selected() {
		_start_index1 = _index1;
		_start_index2 = _index2;
	}

	void next() {
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

	bool execute(Solution<Size>& solution) {
		unsigned int min_index = std::min(_index1, _index2);
		unsigned int max_index = std::max(_index1, _index2);

		std::reverse(&solution._order[min_index], &solution._order[max_index]);

		return _start_index1 != _index1 || _start_index2 != _index2;
	}

private:
	unsigned int _index1;
	unsigned int _index2;

	unsigned int _start_index1;
	unsigned int _start_index2;

};

#endif
