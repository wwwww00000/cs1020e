#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	long jumps, count = 0;
	
	// read input
	cin >> N;
	vector<int> people(N);

	while (cin >> jumps) {
		people[count] = jumps;
		count++;
	}

	cout << "[" << N << " " << count;
	for (int i = 0; i < 10; i++) {
		cout << " " << people[i];
	}
	cout << "]" << endl;

	return 0;
}
