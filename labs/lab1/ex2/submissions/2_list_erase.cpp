#include <iostream>
#include <list>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	list<int> people;
	long jumps;
	
	// read input
	cin >> N;

	for (int i = 0; i < N; i++)
		people.push_back(i);

	list<int>::iterator it = people.begin();

	while (cin >> jumps) {
		for (int i = 0; i < jumps; i++) {
			if (++it == people.end()) {
				it = people.begin();
			}
		}
		it = people.erase(it);
		if (it == people.end()) {
			it = people.begin();
		}
	}

	// display operation
	it = people.begin();
	cout << "[" << *it;
	it++;
	for (; it != people.end(); it++)
		cout << " " << *it;
	cout << "]" << endl;
	
	return 0;
}
