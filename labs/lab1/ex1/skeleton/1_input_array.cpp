#include <iostream>

using namespace std;
#define N_POINTS 500000

void handleFormat1() {
	int N, landmarks[N_POINTS], input, increment = 0;
	cin >> N;
	for (int i = 0; i<N; i++) {
		cin >> input;
		increment += input;
		landmarks[i] = increment;
	}
	// print output
	for (int i = 0; i<N; i++) {
		cout << landmarks[i];
		if (i < N-1)
			cout << " ";
		else
			cout << "\n";
	}
}
void handleFormat2() {
	int landmarks[N_POINTS], increment = 0, count = 0;
	long input = 0;
	while (true) { // true if not sentinel
		cin >> input;
		if (input == -1)
			break;
		increment += input;
		landmarks[count] = increment;
		count++;
	}
	// print output
	for (int i = 0; i<count; i++) {
		cout << landmarks[i];
		if (i < count-1)
			cout << " ";
		else
			cout << "\n";
	}
}
void handleFormat3() {
	long input;
	int landmarks[N_POINTS], increment = 0, count = 0;
	while (cin >> input) { // true if read successful, i.e. not EOF
		increment += input;
		landmarks[count] = increment;
		count++;
	}
	// print output
	for (int i = 0; i<count; i++) {
		cout << landmarks[i];
		if (i < count-1)
			cout << " ";
		else
			cout << "\n";
	}
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
