#include <iostream>
using namespace std;

int main() {
	int a = -1, b = 1, c = 1, d = 0, e = 2, f = 2, g = 0;
	int h = f-- && e++ && d++ && c-- || b++ || a++;
	if (g = 9) {
		cout << a << b << c << d << e << f << g << h << endl;
	} 
	else {
		cout << h << g << f << e << d << c << b << a << endl;
	} 
	return 0;
}
