#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool is_earlier(string appt1, string appt2) {
	// int size1 = appt1.size();
	// int size2 = appt2.size();
	// if (appt1.at[ size1-4 ] < appt2.at[ size2-4 ])
	if ((appt1.rend() - 3) < (appt2.rend() - 3))
		return true;
	else
		return false;
}

int main() {
	for (int j = 0; j < 5; j++) {
		int num_appts;
		cin >> num_appts;
		if (num_appts == 0)
			break;
		vector<string> appts;
		for (int i = 0; i < num_appts; ++i) {
			string appt;
			getline(cin, appt);
			appts.push_back(appt);
		}
		sort(appts.begin(), appts.end(), is_earlier);

		for (string& appt : appts) {
			cout << appt << "\n";
		}
		cout << "\n";
	}
	return 0;
}
