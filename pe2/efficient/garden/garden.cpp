#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

int get_value(int garden[][501], int row, int col) {
	if (garden[row][col] == -1)
		return 0;
	int value = numeric_limits<int>::max();
	if (garden[row-1][col] >= 0)
		value = min(garden[row-1][col], value);
	else 
		value = min(0, value);
	if (garden[row][col-1] >= 0)
		value = min(garden[row][col-1], value);
	else 
		value = min(0, value);
	if (garden[row-1][col-1] >= 0)
		value = min(garden[row-1][col-1], value);
	else 
		value = min(0, value);
	if (value == numeric_limits<int>::max())
		return 1;

	return value + 1;
}

int main() {
	int garden[501][501] = {0};
	int total_rows, total_cols;
	cin >> total_rows >> total_cols;

	for (int i = 1; i < total_rows + 1; ++i) {
		for (int j = 1; j < total_cols + 1; ++j) {
			char input_char;
			cin >> input_char;
			if (input_char == 'o')
				garden[i][j] = -1;
		}
	}

	int num_sub_plots = 0;
	for (int i = 1; i < total_rows + 1; ++i) {
		for (int j = 1; j < total_cols + 1; ++j) {
			int value = get_value(garden, i, j);
			garden[i][j] += value;
			num_sub_plots += value;
		}
	}

	cout << num_sub_plots << '\n';

	return 0;
}
