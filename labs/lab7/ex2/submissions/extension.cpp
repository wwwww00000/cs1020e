#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
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

	long coordinate, final_ans = 0;
	bool has_stepped = true;
	
	// start at the average as an inital guess
	average = sum / num_inputs; 
	coordinate = average;

	pair<long,long> left_change = get_left_change(inputs, coordinate);
	pair<long,long> right_change = get_right_change(inputs, coordinate);
	
	// take steps as long as the target function decreases
	if (left_change.first <= 0) {
		bool handle_last = false;
		while (left_change.first <= 0) {
			if (left_change.first == 0) {
				++num_sat;
				num_arr_sat += left_change.second;
				if (has_stepped) {
					final_ans = coordinate;
					has_stepped = false;
				}
				else
					final_ans = min(final_ans, coordinate);
			}
			--coordinate;
			left_change = get_left_change(inputs, coordinate);
			handle_last = true;
		}
		if (handle_last) {
			++num_sat;
			num_arr_sat += right_change.second;
		}
	}

	coordinate = average;
	if (right_change.first <= 0) {
		bool handle_last = false;
		while (right_change.first <= 0) {
			if (right_change.first == 0) {
				++num_sat;
				num_arr_sat += right_change.second;
				if (has_stepped) {
					final_ans = coordinate;
					has_stepped = false;
				}
			}
			++coordinate;
			right_change = get_right_change(inputs, coordinate);
			handle_last = true;
		}
		if (handle_last) {
			++num_sat;
			num_arr_sat += right_change.second;
		}
	}

	if (has_stepped) { // no steps are taken
		final_ans = average;
		num_sat = 1;
		auto range = equal_range(inputs.begin(), inputs.end(), final_ans);
		num_arr_sat = range.second - range.first;
	}

	cout << final_ans << " " << num_arr_sat << " " << num_sat << "\n";

	return 0;
}
