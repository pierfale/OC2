#ifndef _SOLUTION_H
#define _SOLUTION_H

#include <algorithm>

template<unsigned int Size>
class Solution {

public:
	Solution() {

	}

	void initialize() {
		std::iota(&_order[0], &_order[Size], 0);
	}

	unsigned int _order[Size];
};

#endif
