#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int num_inversions = 0;

bool compare(int left, int right) {
	if (left < right)
		return true;
	else {
		++num_inversions;
		return false;
	}
}

void merge_sort(vector<int>& vec, int low, int high);

int main() {
	int num_elements;
	int num_intervals = 0;
	vector<int> vec;

	cin >> num_elements;
	int sum = 0;
	for (int i = 0; i < num_elements; ++i) {
		int element;
		cin >> element;
		if (element > 0)
			++num_intervals;
		sum += element;
		vec.push_back(sum);
	}
	merge_sort(vec, 0, num_elements);

	cout << num_inversions << "\n";
	cout << num_intervals + num_inversions << "\n";

	return 0;
}

void merge_sort(vector<int>& vec, int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		merge_sort(vec, low, mid);
		merge_sort(vec, mid + 1, high);
		merge(vec.begin() + low, vec.begin() + mid, vec.begin() + mid + 1,
				vec.begin() + high, vec.begin() + low, compare);
	}
}
