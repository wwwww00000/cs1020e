#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int num_cases;
	cin >> num_cases;

	for (int i = 0; i < num_cases; ++i) {
		int size;
		cin >> size;
		vector<int> v1;
		vector<int> v2;
		
		for (int j = 0; j < size; ++j) {
			int input;
			cin >> input;
			v1.push_back(input);
		}
		for (int j = 0; j < size; ++j) {
			int input;
			cin >> input;
			v2.push_back(input);
		}

		sort(v1.begin(), v1.end());
		sort(v2.begin(), v2.end());

		long long product = 0;

		for (int j = 0; j < size; ++j) {
			product += v1[size-j-1] * v2[j];
		}

		cout << "Case #" << i+1 << ": " << product << "\n";
	}
}
