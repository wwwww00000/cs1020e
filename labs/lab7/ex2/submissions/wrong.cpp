#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits> // std:numeric_limits<long>::max() to simplify calculations
using namespace std;

// returns the change in the objective function from taking one step to the left
pair<long,long> get_left_change(vector<long>& vec, long coordinate) {
	vector<long>::iterator lower_it = lower_bound(vec.begin(), vec.end(),
		coordinate);
	long equal_count = 0;
	long num_left = lower_it - vec.begin();
	while (*lower_it == coordinate) {
		++equal_count;
		++lower_it;
	}
	return make_pair((vec.size() - num_left) - num_left, equal_count);
}

// returns the change in the objective function from taking one step to the right
pair<long,long> get_right_change(vector<long>& vec, long coordinate) {
	vector<long>::iterator upper_it = upper_bound(vec.begin(), vec.end(),
		coordinate);
	long equal_count = 0;
	long num_right = vec.end() - upper_it;
	while (*(--upper_it) == coordinate) {
		++equal_count;
	}
	return make_pair((vec.size() - num_right) - num_right, equal_count);
}

int main() {
	unsigned long long sum = 0;
	vector<long> inputs;
	long average, num_inputs, num_sat = 0, num_arr_sat = 0;

	cin >> num_inputs;
	for (long i = 0; i < num_inputs; ++i) {
		long input;
		cin >> input;
		sum += input;
		inputs.push_back(input);
	}
	sort(inputs.begin(), inputs.end());

	long coordinate, final_ans = numeric_limits<long>::max();
	bool has_stepped = false; // TODO
	
	// start at the average as an inital guess
	average = sum / num_inputs; 
	coordinate = average;

	pair<long,long> left_change = get_left_change(inputs, coordinate);
	pair<long,long> right_change = get_right_change(inputs, coordinate);

	long left_steps = 0;
	long right_steps = 0;
	
	// take steps as long as the target function decreases
	if (left_change.first <= 0) {
		// bool handle_last = false;
		while (left_change.first <= 0) {
			// handle_last = false;
			if (left_change.first == 0) {
				++num_sat;
				num_arr_sat += left_change.second;
				final_ans = min(final_ans, coordinate);
				// handle_last = true;
			}
			--coordinate;
			left_change = get_left_change(inputs, coordinate);
			left_steps += 1;
			has_stepped = true;
		}
		++num_sat;
		num_arr_sat += right_change.second;
		final_ans = min(final_ans, coordinate);
	}

	coordinate = average;
	if (right_change.first <= 0) {
		// bool handle_last = false;
		while (right_change.first <= 0) {
			// handle_last = false;
			if (right_change.first == 0) {
				++num_sat;
				num_arr_sat += right_change.second;
				final_ans = min(final_ans, coordinate);
				// handle_last = true;
			}
			++coordinate;
			right_change = get_right_change(inputs, coordinate);
			right_steps += 1;
			has_stepped = true;
		}
		++num_sat;
		num_arr_sat += right_change.second;
	}

	if (!has_stepped) { // no steps are taken
		final_ans = average;
		num_sat = 1;
		pair<vector<long>::iterator,vector<long>::iterator> bounds =
			equal_range(inputs.begin(), inputs.end(), final_ans);
		num_arr_sat = bounds.second - bounds.first;
	}

	cout << final_ans << " " << num_arr_sat << " " << num_sat << "\n";
	// cout << sum / num_inputs << "\n";
	// cout << final_ans << " " << left_steps << " " << right_steps << '\n';

	return 0;
}
