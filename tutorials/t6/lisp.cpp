#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

bool is_operator_str(string str) {
	return (str == "+" || str == "-" || str == "*" || str == "/");
}

double evaluate(vector<string>& args, string operator_str) {
	double output;
	if (operator_str == "+") {
		output = 0;
		for (unsigned int i = 0; i < args.size(); ++i) {
			output += stod(args[i]);
		}
	}
	else if (operator_str == "-") {
		if (args.size() > 1) {
			output = stod(args[0]);
			for (unsigned int i = 1; i < args.size(); ++i) {
				output -= stod(args[i]);
			}
		}
		else {
			output = 0 - stod(args[0]);
		}
	}
	else if (operator_str == "*") {
		output = 1;
		for (unsigned int i = 0; i < args.size(); ++i) {
			output *= stod(args[i]);
		}
	}
	else if (operator_str == "/") {
		if (args.size() > 1) {
			output = stod(args[0]);
			for (unsigned int i = 1; i < args.size(); ++i) {
				output /= stod(args[i]);
			}
		}
		else {
			output = 1 / stod(args[0]);
		}
	}
	return output;
}

int main() {
	string curr_input;
	stack<string> buffer_stack;
	double final_output = 0;

	while (cin >> curr_input) {
		if (curr_input == "(") {
			string operator_str;
			cin >> operator_str;
			buffer_stack.push(operator_str);
		}
		else if (curr_input == ")") {
			vector<string> arguments;
			string retrieved = buffer_stack.top();
			buffer_stack.pop();
			while (!is_operator_str(retrieved)) {
				arguments.push_back(retrieved);
				retrieved = buffer_stack.top();
				buffer_stack.pop();
			}
			double result = evaluate(arguments, retrieved);
			if (!buffer_stack.empty()) {
				ostringstream os;
				os << result;
				buffer_stack.push(os.str());
			}
			else {
				final_output = result;
			}
		}
		else {
			buffer_stack.push(curr_input);
		}
	}

	cout << final_output << '\n';

	return 0;
}
