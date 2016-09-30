#include <algorithm>
#include <ctgmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

class Rectangle {
	// member variables here
	/* TODO */
	long double getCenterY() { return -1; }
  public:
	/* TODO */
	Rectangle() {}
	Rectangle(long x1, long y1, long x2, long y2) {}
	long double computeDistanceFrom(Rectangle other) { return -1; }
	long double getCenterX() { return -1; }
	bool isCenterLeftOf(Rectangle other) { return false; }
	bool isCenterBelow(Rectangle other) { return false; }
};
bool compXAsc(Rectangle left, Rectangle right) { return left.isCenterLeftOf(right); } // x2 comparators
bool compYAsc(Rectangle left, Rectangle right) { return left.isCenterBelow(right); }
bool skeletonCompare(Rectangle left, Rectangle right) { return false; } // delete this as you decide which other comp to use
istream& operator>>(istream& is, Rectangle& rect) {
	long x1, y1, x2, y2;
	is >> x1 >> y1 >> x2 >> y2;
	rect = Rectangle(x1, y1, x2, y2);
	return is;
}

void mergeYXAsc(Rectangle* rectangles, Rectangle* buffer, long lowIdx, long midIdx, long hiIdx) {
	merge(rectangles + lowIdx, rectangles + midIdx + 1, // [low..mid]
		rectangles + midIdx + 1, rectangles + hiIdx + 1, // [mid+1..hi]
		buffer + lowIdx, skeletonCompare); /* TODO : which comparator to use? */
	for (int arrIdx = lowIdx; arrIdx <= hiIdx; arrIdx++) // copy back
		rectangles[arrIdx] = buffer[arrIdx];
}
long double computeMinDist(Rectangle* rectangles, Rectangle* buffer, long lowIdx, long hiIdx) {
	return -1; /* TODO : compute nearest two rectangles */
}
long double computeMinDist(Rectangle* rectangles, long numRects) { // mutates rects
	/* TODO */
	Rectangle* buffer = new Rectangle[numRects];
	long double minDist = computeMinDist(rectangles, buffer, 0, numRects - 1);
	delete [] buffer;
	return minDist;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	long numRects;
	cin >> numRects;
	Rectangle* rectangles = new Rectangle [numRects];
	/* TODO : process input */
	
	cout << computeMinDist(rectangles, numRects) << "\n"; /* TODO : properly format output */
	
	delete [] rectangles;
	return 0;
}
