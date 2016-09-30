#include <iostream>
#include <sstream>
#include <string>
#include <utility>
using namespace std;

typedef pair<long,long> Point;

// returns the intersection of two intervals
pair<long,long> interval_intersect(long start1, long end1, long start2, long end2) {
	long start, end, length1, length2;
	start = start1;
	length1 = end1 - start;
	length2 = end2 - start;
	if (length1 < 0 || length2 < 0) {
		return make_pair(0,0);
	}
	end = (length1 < length2) ? end1 : end2;

	length1 = end - start1;
	length2 = end - start2;
	if (length1 < 0 || length2 < 0) {
		return make_pair(0,0);
	}
	start = (length1 < length2) ? start1 : start2;

	return make_pair(start, end);
}

class Rectangle {
	private:
		Point _bottom_left;
		Point _top_right;
	public:
		Rectangle(long x1, long y1, long x2, long y2) {
			long bl_x, bl_y, tr_x, tr_y;
			if (x1 < x2) {
				bl_x = x1;
				tr_x = x2;
			}
			else {
				bl_x = x2;
				tr_x = x1;
			}
			if (y1 < y2) {
				bl_y = y1;
				tr_y = y2;
			}
			else {
				bl_y = y2;
				tr_y = y1;
			}
			_bottom_left = Point(bl_x, bl_y);
			_top_right = Point(tr_x, tr_y);
		}

		string str() { 
			ostringstream os;
			os << "[(" << _bottom_left.first << ", " << _bottom_left.second << "), (" <<
				_top_right.first << ", " << _top_right.second << ")]";
			return os.str(); 
		}

		// the intersection of two rectangles is given by the intervals of
		// intersection in each dimension
		void intersect_with(Rectangle& other) { // will mutate 
			pair<long,long> x_interval = interval_intersect(_bottom_left.first,
				_top_right.first, other._bottom_left.first,
				other._top_right.first);
			pair<long,long> y_interval = interval_intersect(_bottom_left.second, 
				_top_right.second, other._bottom_left.second,
				other._top_right.second); 
			_bottom_left.first = x_interval.first;
			_top_right.first = x_interval.second;
			_bottom_left.second = y_interval.first;
			_top_right.second = y_interval.second;
		}

		bool is_empty() {
			return (_bottom_left.first - _top_right.first == 0) || 
				(_bottom_left.second - _top_right.second == 0);
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
	
	long N;
	Rectangle intersection(0, 0, 0, 0), next(0, 0, 0, 0); // members will have proper values by the time the next line executes
	cin >> N >> intersection; // can extract directly to a Rectangle object
	
	while (N > 1) { // read input / process data
		cin >> next; // can extract directly to a Rectangle object
		intersection.intersect_with(next);
		if (intersection.is_empty()) {
			cout << "No intersection\n";	
			return 0;
		}
		--N;
	}
	
	// print output
	cout << intersection.str() << "\n";

	return 0;
}
