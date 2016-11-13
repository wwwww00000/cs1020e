#include <iostream>
#include <map>
#include <algorithm>
#include <string>
using namespace std;

int main() {
	int num_cases;
	cin >> num_cases;

	for (int i = 0; i < num_cases; ++i) {
		int substr_len, input_len;
		string input_str;

		cin >> substr_len;
		cin >> input_len;
		cin >> input_str;

		map<string,int> counts;
		for (int j = 0; j <= input_len-substr_len; ++j) {
			string curr_substr =  input_str.substr(j, substr_len);
			map<string,int>::iterator it = counts.find(curr_substr);

			if (it == counts.end()) {
				counts[curr_substr] = 1;
			}
			else {
				it->second += 1;
			}
		}

		// find largest count
		map<string,int>::iterator max_it = max_element(counts.begin(),
			counts.end(), [](const pair<string, int>& pair1, const
			pair<string,int>& pair2) { return pair1.second <
			pair2.second; });

		cout << max_it->first << "\n";
	}

	return 0;
}

