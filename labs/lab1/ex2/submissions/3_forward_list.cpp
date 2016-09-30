#include <iostream>
#include <forward_list>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	forward_list<int> people;
	long jumps;
	
	// read input
	cin >> N;

	for (int i = N-1; i >= 0; i--)
		people.push_front(i);

	forward_list<int>::iterator it = people.begin();
	forward_list<int>::iterator next;

	while (cin >> jumps) {
		for (int i = 0; i < jumps-1; i++) {
			if (++it == people.end()) {
				it = people.begin();
			}
		}

		// removing operation
		next = it;
		if (++next != people.end()) {
			it = people.erase_after(it);

			if (it == people.end())
				it = people.begin();
		}
		else {
			people.pop_front();
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
