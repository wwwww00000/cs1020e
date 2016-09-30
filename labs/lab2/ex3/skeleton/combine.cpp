#include <algorithm>
#include <iostream>
using namespace std;

class Rectangle {
	// member variables here
	/* TODO */
  public:
	Rectangle(long x1, long y1, long x2, long y2) { /* TODO */ }
	bool tryToCombine(Rectangle* other) { /* TODO */ }
	bool isBotLeftXYLessThan(Rectangle* other) { }
	bool isBotLeftYXLessThan(Rectangle* other) { }
};
bool isBotLeftXYLessThan(Rectangle* left, Rectangle* right) { // comparator - leftmost first, NULL last
	if (left == NULL) return false;
	if (right == NULL) return true;
	return left->isBotLeftXYLessThan(right);
}
bool isBotLeftYXLessThan(Rectangle* left, Rectangle* right) { // comparator - bottommost first, NULL last
	if (left == NULL) return false;
	if (right == NULL) return true;
	return left->isBotLeftYXLessThan(right);
}

bool hasCombined(Rectangle** rectangles, long numRects) {
	return false; /* TODO */
}
void combineRectangles(Rectangle** rectangles, long numRects) {
	/* TODO */
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	long numRects;
	cin >> numRects;
	Rectangle** rectangles = new Rectangle* [numRects]; // each arr element is a pointer to a Rect object

	// read input
	/* TODO */
	
	combineRectangles(rectangles, numRects); // perform operation
	
	int numRectsLeft = 0;
	for (long idx = 0; idx < numRects; idx++) { // process result
		/* TODO */
		delete rectangles[idx];
	}
	cout << numRectsLeft << "\n"; // output result
	
	delete [] rectangles;
	return 0;
}
