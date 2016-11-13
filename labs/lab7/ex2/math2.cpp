#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	vector<long> inputs;
	long num_inputs; 

	cin >> num_inputs;
	for (long i = 0; i < num_inputs; ++i) {
		long input;
		cin >> input;
		inputs.push_back(input);
	}
	sort(inputs.begin(), inputs.end());

	// a vector of the change in the objective function from taking a step to
	// the right at the given coordinate
	vector<long> difference(inputs[num_inputs-1] - inputs[0], 0);
	vector<long>::iterator it = inputs.begin();
	long num_left = 0; 
	long right_idx = difference.size() + 1; // a right bound for the minimum plateau
 	for (unsigned long i = 0; i < difference.size(); ++i) {
		long coordinate = i + inputs[0];
		while (coordinate >= *it) {
			++num_left;
			++it;
			if (it == inputs.end())
				break;
		}
		long coord_diff = num_left - (num_inputs - num_left);
		difference[i] = coord_diff;
		
		// a minimum is reached
		if (coord_diff > 0) {
			right_idx = i + 1;
			break;
		}
	}

	// find the corresponding left bound
	long left_idx = max(right_idx - 1, ((long) 0));
	if (difference.size() > 0) {
		while (left_idx > 0 && difference[left_idx-1] >= 0) {
			--left_idx;
		}
	}

	long final_ans = left_idx + inputs[0];
	long num_sat = right_idx - left_idx;
	long num_arr_sat = 0;
	// find number of currences of satisfactory numbers in the input array
	for (long i = left_idx + inputs[0]; i < right_idx + inputs[0]; ++i) {
		auto bounds = equal_range(inputs.begin(), inputs.end(), i);
		num_arr_sat += bounds.second - bounds.first;
	}

	cout << final_ans << " " << num_arr_sat << " " << num_sat << "\n";

	return 0;
}
