#include <iostream>
#include <list>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	list<char> buffer;
	char input_char;
	list<char>::iterator cursor = buffer.end();

	while (cin >> input_char) {
		switch (input_char) {
			case '!':
				for (list<char>::iterator it = buffer.begin(); it !=
				buffer.end(); ++it) {
					cout << *it;
				}
				cout << '\n';
				break;
			case '[':
				cursor = buffer.begin();
				break;
			case ']':
				cursor = buffer.end();
				break;
			case '<':
				if (cursor != buffer.begin()) {
					--cursor;
					cursor = buffer.erase(cursor);
				}
				break;
			default:
				cursor = buffer.insert(cursor, input_char);
				++cursor;
		}
	}

	return 0;
}
