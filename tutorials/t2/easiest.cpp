#include <iostream>
using namespace std;

int sum_digit(int digit) {
	int sum = 0;
	while (digit > 0) {
		sum += digit % 10;
		digit = digit / 10;
	}
	return sum;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	long N, p;

	while (cin >> N) {
		if (N == 0)
			break;
		p = 11;
		while (sum_digit(p * N) != sum_digit(N)) {
			++p;
		}
		cout << p << "\n";
	}

	return 0;	
}
