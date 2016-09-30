#include <iostream>

using namespace std;

void handleFormat1() {
	int N, input, landmark = 0;
	cin >> N;
	for (int i = 0; i<N; i++) {
		cin >> input;
		landmark += input;
		cout << landmark;
		if (i < N-1)
			cout << " ";
		else
			cout << "\n";
	}
}
void handleFormat2() {
	int landmark = 0;
	long input = -2, first = 1;
	while (true) { 
		cin >> input;

		if (input != -1 && first != 1) {
			cout << " ";
		}
		else if (input == -1) { // break on -1
			cout << "\n";
			break;
		}
		else { // don't print space for first element
			first = 0;
		}

		landmark += input;
		cout << landmark;
	}
}
void handleFormat3() {
	long input;
	int landmark = 0, first = 1;
	while (cin >> input) { // true if read successful, i.e. not EOF
		landmark += input;
		if (first != 1) {
			cout << " ";
			cout << landmark;
		}
		else {
			cout << landmark;
			first = 0;
		}
	}
	cout << "\n";
}

int main() {
	// remove these 2 lines if using <cstdio>, i.e. scanf() / printf()
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int format; // handle all kinds of different input formats for practice
	cin >> format;
	
	if (format == 1) handleFormat1();
	else if (format == 2) handleFormat2();
	else if (format == 3) handleFormat3();
	
	return 0;
}
