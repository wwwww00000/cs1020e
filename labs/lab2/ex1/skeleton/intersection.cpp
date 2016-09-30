#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Rectangle {

	// memmber variables here
	/* TODO */
	
  public:
	Rectangle(long x1, long y1, long x2, long y2) { /* TODO */ }
	string str() { return "skeleton"; }
	void intersectWith(Rectangle other) { // will mutate 
		/* TODO */
	}
	bool isEmpty() {
		return false; /* TODO */
	}
};
istream& operator>>(istream& is, Rectangle& rect) { // overload the extraction oper
	long x1, y1, x2, y2;
	is >> x1 >> y1 >> x2 >> y2;
	rect = Rectangle(x1, y1, x2, y2); // create temp Rectangle object, and copy its data to rect
	return is;
}
ostream& operator<<(ostream& os, Rectangle& rect) { // overload the insertion oper
	os << rect.str();
	return os;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	long someVar;
	Rectangle intersection(0, 0, 0, 0); // members will have proper values by the time the next line executes
	cin >> someVar >> intersection; // can extract directly to a Rectangle object
	
	while (someVar) { // read input / process data
		/* TODO */
	}
	
	// print output
	/* TODO */

	return 0;
}
