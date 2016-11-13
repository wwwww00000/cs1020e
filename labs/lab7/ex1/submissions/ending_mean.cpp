#include <iostream>
#include <math.h>
using namespace std;

int main() {
	unsigned long long sum = 0;
	int num_inputs;

	cin >> num_inputs;
	for (int i = 0; i < num_inputs; ++i) {
		unsigned long long input;
		cin >> input;
		sum += input;
	}

	cout << round((long double) sum / num_inputs) << '\n';

	return 0;
}
