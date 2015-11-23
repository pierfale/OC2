#include "BenchLogger.h"

unsigned int BenchLogger::_comparaison_number(0);

void BenchLogger::initialize() {
	_comparaison_number = 0;
}

void BenchLogger::on_comparaison() {
	_comparaison_number++;
}


unsigned int BenchLogger::comparaison_number() {
	return _comparaison_number;
}
