#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void cleanUpIdx(vector<string>& pallets) {
	for (int i = 1; i < pallets.size(); ++i) {
		if (pallets[i] == pallets[i-1])
			pallets.erase(pallet.begin() + i);
	}
}

void cleanUpIterator(vector<string>& pallets) {
	for (vector<string>::iterator it = vector.begin()+1; it != pallets.end(); ++it) {
		vector<string>::iterator prev = it;
		--prev;
		if (pallets[it] == pallets[prev])
			pallets.erase(it);
	}
}

long cleanUpRemove(vector<string>& pallets) {
	long removeCount = 0;
	for (vector<string>::iterator it = vector.begin()+1; it != pallets.end(); ++it) {
		vector<string>::iterator prev = it;
		--prev;
		if (*it == *prev) {
			it->clear()
			++removeCount;
		}
	}
	remove(pallets.begin(), pallets.end(), "");
	return removeCount;
}

int main() {
	return 0;
}
