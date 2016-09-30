#include <ctgmath>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Rectangle {
	// member variables here
	/* TODO */
  public:
  	Rectangle()  /* TODO */ {}
	Rectangle(long x1, long y1, long x2, long y2) { /* TODO */ }
	string str() { return "skeleton"; /* TODO */ }
	long double computeSquaredDistanceFrom(long x, long y) { // squared distance
		/* TODO */
	}
	bool isHigherThan(Rectangle other) { /* TODO */ }
	bool isMoreLeftThan(Rectangle other) { /* TODO */ }
};
istream& operator>>(istream& is, Rectangle& rect) {
	long x1, y1, x2, y2;
	is >> x1 >> y1 >> x2 >> y2;
	rect = Rectangle(x1, y1, x2, y2);
	return is;
}
ostream& operator<<(ostream& os, Rectangle& rect) {
	os << rect.str();
	return os;
}

Rectangle findNearestRectTo(long x, long y, Rectangle* rectangles, long numRects) {
	return Rectangle(); /* TODO */
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	long numRects;
	cin >> numRects;
	Rectangle* rectangles = new Rectangle [numRects]; // heap memory has more space
	// process input
	/* TODO */
	
	long someVar;
	while (cin >> someVar) {
		// process and output
		/* TODO */
	}
	
	delete [] rectangles; // free up the array on the heap
	return 0;
}
