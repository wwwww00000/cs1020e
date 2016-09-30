#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef tree<
	int,
	null_type,
	less<int>,
	rb_tree_tag,
	tree_order_statistics_node_update> 
order_statistic_tree;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	order_statistic_tree people;
	long jumps, position = 0;
	
	// read input
	cin >> N;

	for (int i = 0; i < N; i++)
		people.insert(i);

	while (cin >> jumps) {
		position = (position + jumps) % N;
		people.erase(*people.find_by_order(position));
		N--;
	}

	// display operation
	auto it = people.find_by_order(0);	
	cout << "[" << *it;
	for (int i = 1; i < N; i++) {
		it++;
		cout << " " << *it;
	}
	cout << "]" << endl;
	
	return 0;
}
