#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

void handleInput(string input) {
	istringstream iss(input);
	string word;
	vector<string> words;
	while (iss >> word) {
		words.push_back(word);
	}
	if (words[0] == "Simon" && words[1] == "says") {
		for (long i = 2; i < words.size()-1; i++)
			cout << words[i] << " ";
		cout << words[words.size()-1] << "\n";;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string input;
	long num_input;

	getline(cin, input);
	istringstream iss(input);
	iss >> num_input;

	for (long i = 0; i < num_input; i++) {
		getline(cin, input);
		handleInput(input);
	}

	return 0;
}
