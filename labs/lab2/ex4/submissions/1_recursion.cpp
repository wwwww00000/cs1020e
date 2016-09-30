#include <algorithm>
#include <ctgmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

class Rectangle {
	private:
		long _left;
		long _right;
		long _up;
		long _down;
		long double _center_x;
		long double _center_y;
	public:
		// for constructing utility rectangles
		Rectangle(long x, long y) : _center_x(x), _center_y(y) {}
		Rectangle(long x1, long y1, long x2, long y2) {
			_left = min(x1, x2); 
			_right = max(x1, x2);
			_down = min(y1, y2);
			_up = max(y1, y2);
			_center_x = (_right + _left) / 2.0;
			_center_y = (_up + _down) / 2.0;
		}
		long double compute_distance_from(Rectangle other) { 
			long double x_dist, y_dist;
			x_dist = _center_x - other._center_x;
			// cout << "x_dist: " << x_dist << "\n";
			y_dist = _center_y - other._center_y;
			// cout << "y_dist: " << y_dist << "\n";
			//
			// cout << "dist: " << sqrt(x_dist * x_dist + y_dist * y_dist) << "\n";
			return sqrt(x_dist * x_dist + y_dist * y_dist);
		}
		long double get_center_x() { return _center_x; }
		long double get_center_y() { return _center_y; }
		bool is_center_left_of(Rectangle other) { return _center_x < other._center_x; }
		bool is_center_below(Rectangle other) { return _center_y < other._center_y; }
};

long double compute_min_dist_recursive(Rectangle*, long);


bool comp_x_asc(Rectangle* left, Rectangle* right) { 
	return left->is_center_left_of(*right); 
} 

bool comp_y_asc(Rectangle* left, Rectangle* right) {
	return left->is_center_below(*right); 
}

istream& operator>>(istream& is, Rectangle& rect) {
	long x1, y1, x2, y2;
	is >> x1 >> y1 >> x2 >> y2;
	rect = Rectangle(x1, y1, x2, y2);
	return is;
}

long double compute_min_dist_recursive(vector<Rectangle*> sorted_rects, long upper) {
	if (upper == 2) {
		// cout << "number of elements: " << upper << ", min: " <<
			// sorted_rects[0]->compute_distance_from(*sorted_rects[1]) << "\n";
		return sorted_rects[0]->compute_distance_from(*sorted_rects[1]);
	}
	else {
		long double initial_min_dist, column_min_dist, temp_min_dist;
		initial_min_dist = compute_min_dist_recursive(sorted_rects, upper-1);

		auto current_it = sorted_rects.begin() + (upper - 1);
		Rectangle* current_rect = sorted_rects[upper-1];
		long current_x = current_rect->get_center_x();
		long current_y = current_rect->get_center_y();

		Rectangle x_min_rect(current_x - initial_min_dist, 0);
		auto x_min_it = lower_bound(sorted_rects.begin(), sorted_rects.end(),
			&x_min_rect, comp_x_asc);
		if (x_min_it == sorted_rects.end())
			x_min_it = current_it;
		auto x_max_it = sorted_rects.begin() + (upper - 1);
		vector<Rectangle*> column_rects(x_min_it, x_max_it);
		sort(column_rects.begin(), column_rects.end(), comp_y_asc);

		Rectangle y_min_rect(0, current_y - initial_min_dist);
		Rectangle y_max_rect(0, current_y + initial_min_dist);
		auto y_min_it = lower_bound(column_rects.begin(), column_rects.end(),
			&y_min_rect, comp_y_asc);
		auto y_max_it = upper_bound(column_rects.begin(), column_rects.end(),
			&y_max_rect, comp_y_asc);
	
		// initialize column_min to first rect
		if (y_min_it == column_rects.end()) {
			// cout << "number of elements: " << upper << ", min: " <<
				// initial_min_dist << "\n";
			return initial_min_dist;
		}
		else {
			column_min_dist = (*y_min_it)->compute_distance_from(*current_rect);
			++y_min_it;
			for (; y_min_it != y_max_it; ++y_min_it) {
				temp_min_dist = (*y_min_it)->compute_distance_from(*current_rect);
				if (temp_min_dist < column_min_dist)
					column_min_dist = temp_min_dist;
			}
		}
		// cout << "number of elements: " << upper << ", min: " <<
			// min(initial_min_dist, column_min_dist) << "\n";
		return min(initial_min_dist, column_min_dist);
	}
}

long double compute_min_dist(Rectangle** rectangles, long num_rects) {
	vector<Rectangle*> sorted_rects (rectangles, rectangles + num_rects);
	sort(sorted_rects.begin(), sorted_rects.end(), comp_x_asc);
	return compute_min_dist_recursive(sorted_rects, num_rects);
}

int main() {
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL);

	long num_rects;
	cin >> num_rects;
	Rectangle** rectangles = new Rectangle* [num_rects];

	for (long i = 0; i < num_rects; i++) {
		Rectangle* in_ptr = new Rectangle(0, 0, 0, 0);
		cin >> *in_ptr;
		rectangles[i] = in_ptr;
	} 
	
	cout << setprecision(2) << fixed << compute_min_dist(rectangles, num_rects) << "\n"; 
	
	for (long i = 0; i < num_rects; i++) { delete rectangles[i]; } 
	delete [] rectangles;
	return 0;
}
