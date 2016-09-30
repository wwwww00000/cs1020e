#include <iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int a, b, c, d, case_no = 1;
	int det;

	while(cin >> a >> b >> c >> d) {
		det = a * d - b * c;
		cout << "Case " << case_no << ":\n";
		cout << d / det << " " << - b / det << "\n";
		cout << - c / det << " " << a / det << "\n";
		++case_no;
	}

	return 0;	
}
