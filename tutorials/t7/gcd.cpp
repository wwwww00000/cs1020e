#include <iostream>
using namespace std;

int gcd(int a, int b);

int main() {
	int a, b;

	cin >> a >> b;
	cout << gcd(a, b) << "\n";

	return 0;
}

int gcd(int a, int b) {
	int remainder, quotient;
	quotient = a / b;
	remainder= a % b;
	cout << "(" << a << ", " << b << ") " << a << " = " << quotient << " * " <<
		b << " + " << remainder << "\n";
	if (remainder == 0)
		return b;
	else
		return gcd(b, remainder);
}
