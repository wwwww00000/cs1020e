#include <iostream>
#include <utility> // std::pair
#include <algorithm> // std::min
#include <map> // use map instead of unordered_map to avoid writing hash function
using namespace std;

const int NUM_STEPS = 6;
const long BLOCKED = 1000000000; // 1 bil
const int steps[NUM_STEPS] = {1, 3, 5, 6, 7, 8}; // for problem 1

long long findNumWaysToNUS1D(int distance, map<int,long long>& cachedResults) {
	if (distance == 0) // base case
		return 1;

	long long ways = 0;
	for (int i = 0; i < NUM_STEPS; ++i) {
		int remainingDist = distance - steps[i];
		if (remainingDist >= 0) {
			auto cachedResultIt = cachedResults.find(remainingDist);
			// if results are already cached
			if (cachedResultIt != cachedResults.end()) {
				ways += cachedResultIt->second;
			}
			else { // else recursively calculate
				long long newResult;
				newResult = findNumWaysToNUS1D(remainingDist, cachedResults);
				cachedResults[remainingDist] = newResult;
				ways += newResult;
			}
		}
	}
	return ways;
}

// returns both results in a single recursive call
pair<long long,long long> findNumWaysToNUS2D(long long**& grid, int numRows, int
numCols, int currRow, int currCol, map<pair<int, int>,pair<long long,long long>>&
cachedResults) {
	if ((currRow == numRows-1) && (currCol == numCols-1)) // base case
		return make_pair(1, grid[currRow][currCol]);

	pair<long long,long long> result = make_pair(0, BLOCKED);
	if ((currRow < numRows-1) && grid[currRow+1][currCol] != BLOCKED) {
		pair<int, int> coordinates = make_pair(currRow+1, currCol);
		auto cachedResultIt = cachedResults.find(coordinates);

		if (cachedResultIt != cachedResults.end()) { // if result is cached
			result.first += (cachedResultIt->second).first;
			result.second = min((cachedResultIt->second).second, result.second);
		}
		else { // else recursively calculate
			pair<long long,long long> newBottomResult = findNumWaysToNUS2D(grid, numRows,
					numCols, currRow+1, currCol, cachedResults);
			cachedResults[coordinates] = newBottomResult;
			result.first += newBottomResult.first;
			result.second = min(newBottomResult.second, result.second);
		}
	}
	if ((currCol < numCols-1) && grid[currRow][currCol+1] != BLOCKED) {
		pair<int, int> coordinates = make_pair(currRow, currCol+1);
		auto cachedResultIt = cachedResults.find(coordinates);

		if (cachedResultIt != cachedResults.end()) { // if result is cached
			result.first += (cachedResultIt->second).first;
			result.second = min((cachedResultIt->second).second, result.second);
		}
		else { // else recursively calculate
			pair<long long,long long> newRightResult = findNumWaysToNUS2D(grid, numRows,
					numCols, currRow, currCol+1, cachedResults);
			cachedResults[coordinates] = newRightResult;
			result.first += newRightResult.first;
			result.second = min(newRightResult.second, result.second);
		}
	}
	result.second += grid[currRow][currCol];

	return result;
}

// long long findLeastTotalWait([> add parameters as necessary <]) {}

// main() should only call the 3 functions below
long long findNumWaysToNUS1D(int units) {
	// map for storing previous results
	map<int,long long> cachedResults;
	return findNumWaysToNUS1D(units-1, cachedResults);
}

pair<long long,long long> findNumWaysToNUS2D(long long**& grid, int numRows,
int numCols) {
	// map for storing previous results
	map<pair<int, int>,pair<long long,long long>> cachedResults;
	return findNumWaysToNUS2D(grid, numRows, numCols, 0, 0, cachedResults);
}

// long long findLeastTotalWait(long long** grid, int numRows, int numCols) {}

int main() {
	int firstToken, numCols;
	cin >> firstToken; // either (1) units, or, (2) numRows
	if (cin >> numCols) { // problem 2
		int numRows = firstToken;
		long long** grid = new long long*[numRows];
		for (int rowIdx = 0; rowIdx < numRows; rowIdx++) {
			grid[rowIdx] = new long long[numCols];
			for (int colIdx = 0; colIdx < numCols; colIdx++)
				cin >> grid[rowIdx][colIdx];
		}

		pair<long long,long long> result = findNumWaysToNUS2D(grid, numRows, numCols);
		if (result.first)
			cout << result.first << " " << result.second << "\n";
		else
			cout << "Not possible\n";

		for (int rowIdx = 0; rowIdx < numRows; rowIdx++)
			delete [] grid[rowIdx];
		delete [] grid;
	} else { // problem 1
		cout << findNumWaysToNUS1D(firstToken) << endl;
	}
	return 0;
}
