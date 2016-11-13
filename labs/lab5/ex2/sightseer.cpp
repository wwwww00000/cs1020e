#include <iostream>
#include <stack>
using namespace std;

typedef pair<char,int> Unit;

int main() {
	stack<int> peak_stack;
	int curr_peak, num_relative_peaks = 0;

	cin >> curr_peak;
	// stack is always in descending order
	peak_stack.push(curr_peak);

	while (cin >> curr_peak) {
		// counts the relative peaks by popping peaks off the stack
		while (!peak_stack.empty() && (peak_stack.top() < curr_peak)) {
			peak_stack.pop();
			++num_relative_peaks;

			// debug statement
			// cout << "popped\n";
		}
		// don't increment if there are no peaks left
		if (peak_stack.size() > 0)
			++num_relative_peaks;
		// check for duplicates to prevent double counting
		if (peak_stack.empty() || curr_peak != peak_stack.top()) 
			peak_stack.push(curr_peak);
		
		// debug statement
		// cout << curr_peak << ' ' << num_relative_peaks << ' ' <<
		// peak_stack.size() << '\n';
	}
	cout << num_relative_peaks << '\n';

	return 0;
}

