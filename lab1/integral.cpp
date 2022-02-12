#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cmath>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <limits>
#include "get_time.h"
#include "parse_command_line.h"
#include "integral.h"
using namespace std;

#define NUM_ROUNDS 5

int main(int argc, char** argv) {
	commandLine P(argc, argv,
		"[-n num_segs] [-a lower_bound] [-b upper_bound]");
	size_t n = P.getOptionLongValue("-n", 1000000000);
	double low = P.getOptionDoubleValue("-a", 1.0);
	double high = P.getOptionDoubleValue("-b", 2.0);
	typedef std::numeric_limits< double > dbl;
	cout.precision(dbl::max_digits10);
	
	auto f = [&](double x) {return sin(x)*log(x);};
	
	double tot_time = 0.0;
	for (int round = 0; round <= NUM_ROUNDS; round++) {
		timer t; t.start();
		double x = integral(f, n, low, high);
		t.stop();
		double tm = t.get_total();
		cout << "Round " << round << ", time: " << tm << endl;
		cout << "Round " << round << ", result: " << x << endl;
		if (round != 0) tot_time += tm;
	}
	cout << "Average time: " << tot_time/NUM_ROUNDS << endl;
	
	return 0;
}
