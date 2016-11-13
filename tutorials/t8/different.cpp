#include <iostream>
using namespace std;

int main() {
	long long a, b;
	while (cin >> a >> b) {
		if (a < b)
			cout << b - a << "\n";
		else
			cout << a - b << "\n";
	}
	return 0;
}
