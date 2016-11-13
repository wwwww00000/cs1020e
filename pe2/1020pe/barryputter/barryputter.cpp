#include <iostream>
#include <algorithm>
using namespace std;

int get_max_gold(bool (&incidence)[10][10], int (&gold)[10], int& num_chambers, int
		steps_left, int curr_chamber);

int main() {
	int num_chambers, num_steps;
	cin >> num_chambers >> num_steps;
	bool incidence[10][10] = {0};
	int gold[10] = {0};

	for (int i = 0; i < num_chambers; ++i) {
		int chamber_idx, connections;
		cin >> chamber_idx;
		cin >> gold[chamber_idx];
		cin >> connections;
		for (int j = 0; j < connections; ++j) {
			int connection;
			cin >> connection;
			incidence[chamber_idx][chamber_idx + connection] = true;
		}
	}

	cout << get_max_gold(incidence, gold, num_chambers, num_steps, 0) << "\n";

	return 0;
}

int get_max_gold(bool (&incidence)[10][10], int (&gold)[10], int& num_chambers, 
int steps_left, int curr_chamber) {
	if (steps_left == 0)
		return gold[curr_chamber];
	int max_gold = 0;
	for (int i = 0; i < num_chambers; ++i) {
		if (incidence[curr_chamber][i]) {
			max_gold = max(max_gold, get_max_gold(incidence, gold,
						num_chambers, steps_left - 1, i));
		}
	}
	return max_gold + gold[curr_chamber];
}
