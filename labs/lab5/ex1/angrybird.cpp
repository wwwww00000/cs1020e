#include <iostream>
#include <queue>
#include <algorithm> // std::max
using namespace std;

int main() {
	char unit_type;
	int num_risks, unit_fish;
	// max_fish holds the global maximum while curr_total_fish holds the current
	// running count
	int max_fish = 0, curr_total_fish = 0;
	// fish in clear ajacent units are stored in the same buffer.
	int prev_clear_fish = 0, prev_risk_fish = 0, curr_clear_fish = 0; 
	// flag for accounting for the first group
	bool is_first_group = true;
	// fish are grouped and pushed on queue in the unit in which they are
	// displaced. i.e. they are grouped in "C*R" groups where "C*" denotes
	// zero or more clear units
	queue<int> displacement_queue;

	cin >> num_risks;

	while (cin >> unit_type >> unit_fish) {
		// debug statement
		// cout << "before loop: " << prev_clear_fish << " " << prev_risk_fish << " " <<
			// curr_clear_fish << " " << curr_total_fish << " " << max_fish << "\n";

		// accrue clear units to group
		if (unit_type == 'C')
			curr_clear_fish += unit_fish;
		else {
			if (is_first_group) {
				prev_clear_fish = curr_clear_fish;
				curr_clear_fish = 0;
				prev_risk_fish = unit_fish;
				is_first_group = false; 
			}
			else {
				// pops the first displacement group if number of risks is at quota
				if (displacement_queue.size() == num_risks) {
					int fish_to_add = prev_risk_fish + curr_clear_fish;

					// stores the maximum and carries on computation with the
					// rest of the input
					if (fish_to_add < displacement_queue.front() &&
							curr_total_fish + prev_clear_fish > max_fish) {
						max_fish = curr_total_fish + prev_clear_fish;
					}
					curr_total_fish -= displacement_queue.front();
					displacement_queue.pop();
				}

				displacement_queue.push(prev_clear_fish + prev_risk_fish);
				curr_total_fish += prev_clear_fish + prev_risk_fish;
				prev_clear_fish = curr_clear_fish;
				curr_clear_fish = 0;
				prev_risk_fish = unit_fish;
			}
		}
		// debug statement
		// cout << "after loop: " << prev_clear_fish << " " << prev_risk_fish << " " <<
			// curr_clear_fish << " " << curr_total_fish << " " << max_fish << "\n";
	}

	// handle ending balances
	if (displacement_queue.size() < num_risks) {
		curr_total_fish += prev_clear_fish + prev_risk_fish + curr_clear_fish;
	}
	else {
		int fish_to_add = prev_clear_fish + prev_risk_fish +
			curr_clear_fish;
		if (fish_to_add > displacement_queue.front()) {
			curr_total_fish -= displacement_queue.front();
			curr_total_fish += fish_to_add;
		}
		else
			curr_total_fish += prev_clear_fish;
	}

	// debug statement
	// cout << "ending adjustment: " << prev_clear_fish << " " << prev_risk_fish << " " <<
		// curr_clear_fish << " " << curr_total_fish << " " << max_fish << "\n";

	cout << max(max_fish, curr_total_fish) << '\n';

	return 0;
}
