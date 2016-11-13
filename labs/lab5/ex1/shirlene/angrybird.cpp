#include <iostream>
#include <queue>
#include <utility>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	pair<char, int> unit;
	queue<pair<char, int>> numFish;
	char risk;
	int fish, maxRisk;
	int currFish = 0;
	int countRisk = 0;
	int currMaxFish = 0;
	int globalMaxFish = 0;
	// int temp = 0;

	cin >> maxRisk;
	while (cin >> risk >> fish) {
		unit =  make_pair(risk, fish);
		if (unit.first == 'R') {
			++countRisk;
			if (countRisk <= maxRisk) {
				numFish.push(unit);
				currFish += unit.second;
				currMaxFish = currFish;
			}
			else if (countRisk > maxRisk) {
				if (globalMaxFish < currMaxFish) {
					globalMaxFish = currMaxFish;
				}
				while (numFish.front().first!='R') {
					currFish -= numFish.front().second;
					numFish.pop();
					currMaxFish = currFish;
				}
				currFish -= numFish.front().second;
				numFish.pop();
				--countRisk;
				numFish.push(unit);
				// temp = currMaxFish;
				currFish += unit.second;
				currMaxFish = currFish;
				// else if (temp > currMaxFish && globalMaxFish < currMaxFish) {
					// globalMaxFish = temp;
				// }
			}
		}
		else {
			numFish.push(unit);
			currFish += unit.second;
			currMaxFish = currFish;
		}
		// cout << risk << " " << fish << " " << currMaxFish << " " << globalMaxFish << "\n";
	}
	if (globalMaxFish < currMaxFish) {
		globalMaxFish = currMaxFish;
	}
	cout << globalMaxFish << '\n';
	return 0;
}

