#ifndef _INSTANCE_H
#define _INSTANCE_H

template<unsigned int Size, unsigned int Objective>
class Instance {

	friend class ParserTSP;
	friend class Fitness;

public:



private:
	unsigned int _cost[Objective][Size][Size];
};

#endif
