#include <iostream>
#include <math.h>
// #include <cmath>
#include <iomanip> // manipulate I/O
using namespace std;

int main() {
	double r, c; 
	double ans;
	// const double PI = 2 * acos(0.0);

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> r >>  c;
	ans = 100.0 * ((M_PIl * (r-c) * (r-c)) / (M_PIl * r * r));
	cout << fixed << setprecision(9) << ans << "\n";

	return 0;
}
