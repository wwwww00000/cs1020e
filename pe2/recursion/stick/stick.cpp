#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

int get_min_sticks(vector<int>& sticks, int slot_len, int curr_sticks, int
start_idx);

int main() {
	int num_sticks, slot_len;
	cin >> num_sticks >> slot_len;
	vector<int> sticks;

	for (int i = 0; i < num_sticks; ++i) {
		int curr_stick;
		cin >> curr_stick;
		sticks.push_back(curr_stick);
	}

	int result = get_min_sticks(sticks, slot_len, 0, 0);

	if (result == numeric_limits<int>::max())
		cout << "-1\n";
	else
		cout << result << '\n';

	return 0;
}

int get_min_sticks(vector<int>& sticks, int slot_len, int curr_sticks, int
start_idx) {
	if (slot_len == 0) {
		return curr_sticks;
	}
	if (slot_len <= 0) {
		return numeric_limits<int>::max();
	}
	if (start_idx == sticks.size()) {
		return numeric_limits<int>::max();
	}
	return min(get_min_sticks(sticks, slot_len - sticks[start_idx], curr_sticks
				+ 1, start_idx + 1),
				get_min_sticks(sticks, slot_len, curr_sticks, start_idx + 1));
}
