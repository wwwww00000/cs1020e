#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool compare_sans_case(string& str1, string& str2) {
	transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
	transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
	return str1 < str2;
}

int main() {
	int num_lines, num_chars;
	bool first = true;
	while (true) {
		cin >> num_lines >> num_chars;
		if (num_lines == 0)
			break;
		if (first) {
			first = false;
		}
		else {
			cout << "\n";
		}
		vector<string> cols(num_chars, "");
		for (int i = 0; i < num_lines; ++i) {
			string row;
			cin >> row;
			for (int j = 0; j < num_chars; ++j) {
				cols[j] = cols[j] + row.substr(j, 1);
			}
		}
		stable_sort(cols.begin(), cols.end(), compare_sans_case);

		// print output
		for (int i = 0; i < num_lines; ++i) {
			for (int j = 0; j < num_chars; ++j) {
				cout << cols[j].at(i);
			}
			cout << "\n";
		}
	}
	return 0;
}
