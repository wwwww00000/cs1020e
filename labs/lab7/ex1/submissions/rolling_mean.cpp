#include <iostream>
#include <math.h>
using namespace std;

int main() {
	long double average = 0;
	int num_inputs;

	cin >> num_inputs;
	for (int i = 0; i < num_inputs; ++i) {
		long input;
		cin >> input;
		average *= (long double) i / (i + 1);
		average += (long double) input / (i + 1);
	}

	cout << round(average) << '\n';

	return 0;
}
