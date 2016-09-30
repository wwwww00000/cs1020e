#include <cstdio>
#include <list>
using namespace std;

int main() {
	int N;
	list<int> people;
	long jumps;
	
	// read input
	scanf("%d\n", &N);

	for (int i = 0; i < N; i++)
		people.push_back(i);

	list<int>::iterator it = people.begin();

	while (scanf("%ld", &jumps) != EOF) {
		for (int i = 0; i < jumps; i++) {
			if (++it == people.end()) {
				it = people.begin();
			}
		}
		it = people.erase(it);
		if (it == people.end()) {
			it = people.begin();
		}
	}

	// display operation
	it = people.begin();
	printf("[%d", *it);
	it++;
	for (; it != people.end(); it++)
		printf(" %d", *it);
	printf("]\n");
	
	return 0;
}
