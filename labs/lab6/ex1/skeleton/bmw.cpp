#include <iostream>
using namespace std;

const int NUM_STEPS = 6;
const int steps[NUM_STEPS] = {1, 3, 5, 6, 7, 8};

long findNumWaysToNUSRecursive(int distance) {
	if (distance == 0) // base case
		return 1;

	int ways = 0;
	// recursively calculate results
	for (int i = 0; i < NUM_STEPS; ++i) {
		if (distance - steps[i] >= 0)
			ways += findNumWaysToNUSRecursive(distance-steps[i]);
	}
	return ways;
}

// main() should always call this function below
long findNumWaysToNUS(int units) {
	return findNumWaysToNUSRecursive(units-1);
}


int main() {
	int units;
	cin >> units;
	cout << findNumWaysToNUS(units) << endl;
	return 0;
}
