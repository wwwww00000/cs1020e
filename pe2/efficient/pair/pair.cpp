#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main() {
	int num_people;
	vector<int> contestants;
	map<int,int> teams_per_bracket;

	cin >> num_people;
	for (int i = 0; i < num_people; ++i) {
		int person;
		cin >> person;
		contestants.push_back(person);
	}

	for (int i = 0; i < num_people; ++i) {
		for (int j = i + 1; j < num_people; ++j) {
			int bracket = contestants[i] + contestants[j];
			auto it = teams_per_bracket.find(bracket);
			if (it == teams_per_bracket.end())
				teams_per_bracket[bracket] = 1;
			else 
				it->second += 1;
		}
	}

	int total_pairings = 0;
	for (pair<const int,int>& element : teams_per_bracket) {
		if (element.second > 1) {
			total_pairings += 4 * element.second * (element.second - 1);
			// total_pairings += 8 * element.second * (element.second - 1) / 2;
		}
	}
	cout << total_pairings << '\n';

	return 0;
}
