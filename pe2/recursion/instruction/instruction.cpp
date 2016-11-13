#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

int operate(int curr_result, pair<char,int> operation);

int get_closest(vector<pair<char,int>>& operations, int target, int
curr_result, int start_idx);

int main() {
	int num_inputs, target;
	cin >> num_inputs >> target;
	vector<pair<char,int>> operations;

	for (int i = 0; i < num_inputs; ++i) {
		char instr_char;
		int instr_num;
		cin >> instr_char >> instr_num;
		operations.push_back(make_pair(instr_char, instr_num));
	}
	
	int result = get_closest(operations, target, 0, 0);
	cout << result << '\n';

	return 0;
}

int get_closest(vector<pair<char,int>>& operations, int target, int
curr_result, int start_idx) {
	if (start_idx == operations.size()) {
		return curr_result;
	}
	int include = get_closest(operations, target, operate(curr_result,
					operations[start_idx]), start_idx + 1);
	int exclude = get_closest(operations, target, curr_result, start_idx + 1);
	int include_diff = abs(include - target);
	int exclude_diff = abs(exclude - target);
	if (include_diff < exclude_diff)
		return include;
	else if (include_diff > exclude_diff)
		return exclude;
	else 
		return min(include, exclude);
}

int operate(int curr_result, pair<char,int> operation) {
	switch (operation.first) {
		case '+' :
			return curr_result + operation.second;
		case '*' :
			return curr_result * operation.second;
		case '-' :
			return curr_result - operation.second;
		default :
			return curr_result / operation.second;
	}
}
