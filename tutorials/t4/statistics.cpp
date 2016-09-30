#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Machine {
	private:
		int _min;
		int _max;
		int _range;
	public:
		Machine(){
			_max = -1000000;
			_min = 1000000;
			_range = 0;
		}

		void read(int n) {
			int x;
			while (n--) {
				cin >> x;
				_min = min(_min, x);
				_max = max(_max, x);
			}
			_range = _max - _min;
		}

		void report(int k) {
				cout << "Case " << k << ": " << _min << ' ' <<
					_max << ' ' << _range << '\n';
		}

		void refresh() {
			_max = -1000000;
			_min = 1000000;
			_range = 0;
		}
};

int main() {
	int k = 1, n;
	Machine M;

	while (cin >> n) {
		M.read(n);
		M.report(k++);
		M.refresh();
	}

	return 0;
}
