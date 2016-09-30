#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	long jumps, position = 0;
	
	// read input
	cin >> N;
	
	vector<int> vec(N);
	iota(vec.begin(), vec.end(), 0);

	while (cin >> jumps) {
		position += jumps;
		position %= N;
		vec.erase(vec.begin() + position);
		N--;
	}

	// display operation
	cout << "[";
	copy(vec.begin(), vec.end()-1, ostream_iterator<int>(cout, " "));
	cout << vec[N-1] << "]" << endl;
	
	return 0;
}
