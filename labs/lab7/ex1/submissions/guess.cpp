#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// returns the change in the objective function from taking one step to the left
long get_left_change(vector<long>& vec, long coordinate) {
	vector<long>::iterator lower_it = lower_bound(vec.begin(), vec.end(),
		coordinate);
	long num_left = lower_it - vec.begin();
	return (vec.size() - num_left) - num_left;
}

// returns the change in the objective function from taking one step to the right
long get_right_change(vector<long>& vec, long coordinate) {
	vector<long>::iterator upper_it = upper_bound(vec.begin(), vec.end(),
		coordinate);
	long num_right = vec.end() - upper_it;
	return (vec.size() - num_right) - num_right;
}

int main() {
	unsigned long long sum = 0;
	vector<long> inputs;
	long num_inputs, curr_ans;

	cin >> num_inputs;
	for (long i = 0; i < num_inputs; ++i) {
		long input;
		cin >> input;
		sum += input;
		inputs.push_back(input);
	}
	sort(inputs.begin(), inputs.end());

	// start at the average as an inital guess
	curr_ans = sum / num_inputs; 
	long left_change = get_left_change(inputs, curr_ans);
	long right_change = get_right_change(inputs, curr_ans);
	// take steps as long as the target function decreases
	// problem is convex i.e. no local minima
	if (left_change < 0) {
		while (left_change < 0) {
			--curr_ans;
			left_change = get_left_change(inputs, curr_ans);
		}
	}
	else if (right_change < 0) {
		while (right_change < 0) {
			--curr_ans;
			right_change = get_right_change(inputs, curr_ans);
		}
	}

	cout << curr_ans << '\n';

	return 0;
}
