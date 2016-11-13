#include <iostream>
#include <math.h>
#include <vector>
#include <stack>
#include <utility>
using namespace std;

typedef long long LL;

LL calculate_rooms(LL width, LL height) {
	return (width + 1) * width * (height + 1) * height / 4;
}

int main() {
	LL num_towers;
	vector<LL> towers;
	stack<pair<LL,LL>> tower_stack;

	cin >> num_towers;
	for (LL i = 0; i < num_towers; ++i) {
		LL tower;
		cin >> tower;
		towers.push_back(tower);
	}
	
	LL total_rooms = 0;
	tower_stack.push(make_pair(towers[0], 1));
	for (LL i = 1; i < num_towers; ++i) {
		if (tower_stack.top().first > towers[i]) { // high to low
			LL curr_width = 1;
			pair<LL,LL> curr_tower = tower_stack.top(); 
			tower_stack.pop();

			while (!tower_stack.empty() && tower_stack.top().first >= towers[i]) {
				LL difference = curr_tower.first - tower_stack.top().first;
				total_rooms += calculate_rooms(curr_tower.second, abs(difference));
				total_rooms += abs(difference) * tower_stack.top().first *
					(curr_tower.second + 1) * curr_tower.second / 2;
				curr_tower.second += tower_stack.top().second;
				curr_tower.first = tower_stack.top().first;
				tower_stack.pop();
			}
			total_rooms += calculate_rooms(curr_tower.second, curr_tower.first -
					towers[i]);
			total_rooms += (curr_tower.first - towers[i]) *
				towers[i] * (curr_tower.second + 1) *
				curr_tower.second / 2;
			curr_width += curr_tower.second;

			tower_stack.push(make_pair(towers[i], curr_width));
		}
		else if (tower_stack.top().first == towers[i]) {
			tower_stack.top().second += 1;
		}
		else { // low to high
			tower_stack.push(make_pair(towers[i], 1));
		}
	}

	LL curr_width = 0;
	while (tower_stack.size() > 1) {
		pair<LL,LL> curr_tower = tower_stack.top(); 
		tower_stack.pop();
		curr_tower.second += curr_width;
		LL difference = curr_tower.first - tower_stack.top().first;

		total_rooms += calculate_rooms(curr_tower.second, difference);
		total_rooms += difference * tower_stack.top().first *
			(curr_tower.second + 1) * curr_tower.second / 2;
		curr_width = curr_tower.second;
	}
	tower_stack.top().second += curr_width;
	total_rooms += calculate_rooms(tower_stack.top().second, tower_stack.top().first);

	cout << total_rooms << "\n";

	return 0;
}
