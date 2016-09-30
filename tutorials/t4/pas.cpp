#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

class Sequence {
	private:
		vector<int> _sequence;
		vector<int> _sorted;
	public:
		Sequence(string input) {
			istringstream is(input);
			int N;
			is >> N;
			for (int i = 0; i < N; i++) {
				int n;
				is >> n;
				_sequence.push_back(n);
			}
			_sorted = _sequence;
			sort(_sorted.begin(), _sorted.end());
		}

		bool is_arithmetic() {
			int prev_increment = _sequence[1] - _sequence[0];
			
			for (unsigned int i = 0; i < _sequence.size() - 1; ++i) {
				if (_sequence[i+1] - _sequence[i] != prev_increment)
					return false;
			}

			return true;
		}

		bool is_permuted_arithmetic() {
			int prev_increment = _sorted[1] - _sorted[0];
			
			for (unsigned int i = 0; i < _sorted.size() - 1; ++i) {
				if (_sorted[i+1] - _sorted[i] != prev_increment)
					return false;
			}

			return true;
		}

		void display() {
			if (is_arithmetic()) {
				cout << "arithmetic\n";
				return;
			}
			if (is_permuted_arithmetic()) {
				cout << "permuted arithmetic\n";
				return;
			}
			cout << "non-arithmetic\n";
		}
};

int main() {
	string input;
	int N;

	getline(cin, input);
	istringstream is(input);
	is >> N;

	for (int i = 0; i < N; i++) {
		getline(cin, input);
		Sequence seq(input);
		seq.display();
	}

	return 0;
}
