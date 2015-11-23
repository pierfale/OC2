#ifndef _PARSER_TSP_H
#define _PARSER_TSP_H

#include <fstream>
#include <stdexcept>
#include <cstdarg>

#include "Instance.h"

class ParserTSP {

public:
	template<unsigned int Size, unsigned int Objective>
	static void execute(Instance<Size, Objective>& instance, ...) {

		va_list args;
		va_start(args, instance);

		for(unsigned int objective_index=0; objective_index<Objective; objective_index++) {
			const char* filename = va_arg(args, const char*);
			std::ifstream file(filename , std::ios::in);


			if(file) {
				std::string line;

				// Header
				std::getline(file, line);
				std::getline(file, line);
				std::getline(file, line);
				std::getline(file, line);
				std::getline(file, line);
				std::getline(file, line);
				std::getline(file, line);

				// Content
				for(unsigned int x=0; x<Size; x++) {
					for(unsigned int y=x; y<Size; y++) {
						unsigned int n;
						file >> n;

						instance._cost[objective_index][x][y] = n;
						instance._cost[objective_index][y][x] = n;
					}
				}


				file.close();
			}
			else
				throw std::runtime_error("Unable to open "+std::string(filename));
		}

		va_end(args);
	}


};

#endif
