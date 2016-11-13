#include <iostream>
using namespace std;
#define CANVAS_SIZE 8

void fill(int arr[][CANVAS_SIZE+2], int currRow, int currCol, int newColour);
void fill(int arr[][CANVAS_SIZE+2], int currRow, int currCol, int
		initialColour, int newColour);

void input(int arr[][CANVAS_SIZE+2]);
void output(int arr[][CANVAS_SIZE+2]);

int main() {
	int canvas[CANVAS_SIZE+2][CANVAS_SIZE+2];
	int startRow, startCol, newColour;

	input(canvas);
	cin >> startRow >> startCol >> newColour;
	fill(canvas, startRow+1, startCol+1, newColour);
	output(canvas);

	return 0;
}

void fill(int arr[][CANVAS_SIZE+2], int currRow, int currCol, int newColour) {
	fill(arr, currRow, currCol, arr[currRow][currCol], newColour);
}

void fill(int arr[][CANVAS_SIZE+2], int currRow, int currCol, int
initialColour, int newColour) {
	arr[currRow][currCol] = newColour;

	if (arr[currRow+1][currCol] == initialColour)
		fill(arr, currRow+1, currCol, initialColour, newColour);
	if (arr[currRow-1][currCol] == initialColour)
		fill(arr, currRow-1, currCol, initialColour, newColour);
	if (arr[currRow][currCol+1] == initialColour)
		fill(arr, currRow, currCol+1, initialColour, newColour);
	if (arr[currRow][currCol-1] == initialColour)
		fill(arr, currRow, currCol-1, initialColour, newColour);
}

void input(int arr[][CANVAS_SIZE+2]) {
	for (int i = 0; i < CANVAS_SIZE+2; ++i) {
		for (int j = 0; j < CANVAS_SIZE+2; ++j) {
			if (i == 0 || j == 0 || i == 9 || j == 9)
				arr[i][j] = -1;
			else
				cin >> arr[i][j];
		}
	}
}

void output(int arr[][CANVAS_SIZE+2]) {
	for (int i = 1; i < CANVAS_SIZE+1; ++i) {
		for (int j = 1; j < CANVAS_SIZE+1; ++j) {
			cout << arr[i][j] << " ";
		}
		cout << "\n";
	}
}

