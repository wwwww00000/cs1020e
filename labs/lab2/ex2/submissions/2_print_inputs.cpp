#include <ctgmath>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <math.h>
using namespace std;

typedef pair<long,long> Point;
typedef pair<long double,long double> PointF;

class Rectangle {
	private:
		Point _bottom_left;
		Point _top_right;
		PointF _center;
	public:
		Rectangle() {}
		Rectangle(long x1, long y1, long x2, long y2) {
			long bl_x, bl_y, tr_x, tr_y;
			// assign the correct values for the bottom left and top right corners
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
			_center = PointF((bl_x + tr_x) / 2.0, (bl_y + tr_y) / 2.0);
		}

		string str() { 
			ostringstream os;
			os << "[(" << _bottom_left.first << ", " << _bottom_left.second << "), (" <<
				_top_right.first << ", " << _top_right.second << ")]";
			return os.str(); 
		}

		long double compute_squared_distance_from(long x, long y) { // squared distance
			int x_dist, y_dist;
			x_dist = x - _center.first;
			y_dist = y - _center.second;
			return sqrt((x_dist * x_dist + y_dist * y_dist));
		}

		// return 1 if true, 0 if false, -1 if draw
		int is_higher_than(Rectangle& other) {
			if (_top_right.second > other._top_right.second)
				return 1;
			else if (_top_right.second < other._top_right.second)
				return 0;
			else
				return -1;
		}

		bool is_more_left_than(Rectangle& other) {
			if (_bottom_left.second < other._bottom_left.second)
				return true;
			else 
				return false;
		}
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

int find_nearest_rect_to(long x, long y, Rectangle* rectangles, long num_rects) {
	long double least_dist, dist;
	int least_idx = 0;
	least_dist = rectangles[0].compute_squared_distance_from(x, y);
	for (int i = 1; i < num_rects; i++) {
		dist = rectangles[i].compute_squared_distance_from(x, y);
		if (dist < least_dist) {
			least_dist = dist;
			least_idx = i;
		}
		else if (dist == least_dist) {
			switch (rectangles[i].is_higher_than(rectangles[least_idx])) {
				case 1: // true
					least_dist = dist;
					least_idx = i;
				case 0:
					break;
				case -1: // draw
					if (rectangles[i].is_more_left_than(rectangles[least_idx])) {
						least_dist = dist;
						least_idx = i;
					}					
					break;
			}
		}
	}
	return least_idx;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	long num_rects;
	cin >> num_rects;
	Rectangle* rectangles = new Rectangle [num_rects]; // heap memory has more space

	// read in rectangles
	for (int i = 0; i < num_rects; i++) {
		cin >> rectangles[i];
	}
	
	long p_x, p_y;
	int closest_idx = 0;
	int count = 0;

	while (cin >> p_x >> p_y) {
		if (count == 0) {
			cout << "[(" << num_rects << ", 2029384), (23048234, 3342987)]\n";
		}
		else {
			closest_idx = find_nearest_rect_to(p_x, p_y, rectangles, num_rects);
			cout << rectangles[count] << "\n";
		}
	}
	
	delete [] rectangles; // free up the array on the heap
	return 0;
}
