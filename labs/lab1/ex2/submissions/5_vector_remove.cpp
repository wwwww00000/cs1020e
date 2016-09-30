#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	long jumps, position = 0, dead = 0;
	
	// read input
	cin >> N;
	
	vector<int> people(N);
	vector<int>::iterator last = people.end();

	for (int i = 0; i < N; i++)
		people[i] = i;

	while (cin >> jumps) {
		if (position + jumps < N) {
			position += jumps;
			people[position] = -1;
			dead++;
			position++;
		}
		else {
			last = remove(people.begin(), last, -1);
			N -= dead;
			position -= dead;
			dead = 0;

			position = (position + jumps) % N;
			people[position] = -1;
			dead++;
			position++;
		}
	}
	last = remove(people.begin(), last, -1);
	N -= dead;
	position -= dead;
	dead = 0;

	// display operation
	for (int i = 0; i < N; i++) {
		if (i != 0) {
			cout << " " ;
		}
		else {
			cout << "[" ;
		}
		cout << people[i];
	}
	cout << "]" << endl;
	
	return 0;
}
