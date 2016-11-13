#include <iostream>
#include <utility> // std::pair
#include <algorithm> // std::min
using namespace std;

const int BLOCKED = 1000000000; // 1 bil

// returns both results in one recursive call
pair<long,long> findNumWaysToNUS(long**& grid, int numRows, int numCols, int currRow, 
int currCol) {
	if ((currRow == numRows-1) && (currCol == numCols-1))
		return make_pair(1, grid[currRow][currCol]);

	// pair containing the number of ways and the time taken
	pair<long,long> result = make_pair(0, BLOCKED);
	// recursively calculate for coordinates to the left and bottom
	if ((currRow < numRows-1) && grid[currRow+1][currCol] != BLOCKED) {
		pair<long,long> bottomResult = findNumWaysToNUS(grid, numRows,
				numCols, currRow+1, currCol);
		result.first += bottomResult.first;
		// take the minimum of the two times
		result.second = min(bottomResult.second, result.second);
	}
	if ((currCol < numCols-1) && grid[currRow][currCol+1] != BLOCKED) {
		pair<long,long> rightResult = findNumWaysToNUS(grid, numRows,
				numCols, currRow, currCol+1);
		result.first += rightResult.first;
		result.second = min(rightResult.second, result.second);
	}
	result.second += grid[currRow][currCol];

	return result;
}

// long findLeastTotalWait([> add params if necessary <]) {}

// main() should always call the two functions below
pair<long,long> findNumWaysToNUS(long**& grid, int numRows, int numCols) {
	return findNumWaysToNUS(grid, numRows, numCols, 0, 0);
}
// long findLeastTotalWait(long**& grid, int numRows, int numCols) {}

int main() {
	int numRows, numCols;
	cin >> numRows >> numCols;
	long** grid = new long*[numRows];
	for (int rowIdx = 0; rowIdx < numRows; rowIdx++) {
		grid[rowIdx] = new long[numCols];
		for (int colIdx = 0; colIdx < numCols; colIdx++)
			cin >> grid[rowIdx][colIdx];
	}

	pair<long,long> result = findNumWaysToNUS(grid, numRows, numCols);
	if (result.first)
		cout << result.first << " " << result.second << "\n";
	else
		cout << "Not possible\n";

	for (int rowIdx = 0; rowIdx < numRows; rowIdx++)
		delete [] grid[rowIdx];
	delete [] grid;
	return 0;
}
