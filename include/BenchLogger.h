#ifndef _BENCH_LOGGER_H
#define _BENCH_LOGGER_H

class BenchLogger {

public:
	static void initialize();

	static void on_comparaison();


	static unsigned int comparaison_number();

private:
	static unsigned int _comparaison_number;
};

#endif
