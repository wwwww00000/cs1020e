#include <algorithm>
#include <iostream>
#include <algorithm>
#include <utility>
#include <sstream>
using namespace std;

class Rectangle {
	private:
		long _left;
		long _right;
		long _up;
		long _down;
		Rectangle* _combined_with; // pointer to the leftmost or bottom most rectangle that it is combined with
	public:
		Rectangle(long x1, long y1, long x2, long y2) {
			_left = min(x1, x2); 
			_right = max(x1, x2);
			_down = min(y1, y2);
			_up = max(y1, y2);
			_combined_with = NULL;
		}

		// combines rectangles and returns true if appropriate. will mutate both.
		bool try_to_combine(Rectangle* other) {
			if (other->_left == _left && (other->_down == _down && other->_up == _up ) {
				_right = other->_right;
				other->_combined_with = this;
				return true;
			}
			else 
				return false;
		}

		bool is_bot_left_XY_less_than(Rectangle* other) {
			return (_left < other->_left);
		}

		bool is_bot_left_YX_less_than(Rectangle* other) {
			return (_down < other->_down);
		}
};

bool is_bot_left_XY_less_than(Rectangle* left, Rectangle* right) { // comparator - leftmost first, NULL last
	if (left == NULL) return false;
	if (right == NULL) return true;
	return left->is_bot_left_XY_less_than(right);
}

bool is_bot_left_YX_less_than(Rectangle* left, Rectangle* right) { // comparator - bottommost first, NULL last
	if (left == NULL) return false;
	if (right == NULL) return true;
	return left->is_bot_left_YX_less_than(right);
}

// skeleton
// bool has_combined(Rectangle** rectangles, long num_rects) {
	// return false; 
// }

// as no ambiguous cases are given, we can combine in two stages, 
// horizontally then vertically.
void combine_rectangles(Rectangle** rectangles, long num_rects) {
	// first combine in horizontal direction
	sort(rectangles, rectangles + num_rects, is_bot_left_XY_less_than);
	long idx = 0, next;

	// iterate through all rectangles
	while (idx < num_rect) {
		// skip rectangles already combined
		if (rectangles[idx]->_combined_with != NULL) {
			++idx;
			continue;
		}
		next = idx + 1;
		// if combination is successful, keep going until bound is reached
		while (rectangles[next]->_left <= rectangles[idx]->right ||
			rectangles[idx]->try_to_combine(rectangles[next])) {
			++next;
		}
		++idx;
	}
}

istream& operator>>(istream& is, Rectangle& rect) {
	long x1, y1, x2, y2;
	is >> x1 >> y1 >> x2 >> y2;
	rect = Rectangle(x1, y1, x2, y2);
	return is;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	long num_rects;
	cin >> num_rects;
	Rectangle** rectangles = new Rectangle* [num_rects]; // each arr element is a pointer to a Rect object

	for (long i = 0; i < num_rects; i++) {
		rectangles[i] = new Rectangle(0, 0, 0, 0);
		cin >> *rectangles[i];
	} 
	
	combine_rectangles(rectangles, num_rects); // perform operation
	
	int num_rects_left = 0;
	for (long idx = 0; idx < num_rects; idx++) { // process result
		/* TODO */
		delete rectangles[idx];
	}
	cout << num_rects_left << "\n"; // output result
	
	delete [] rectangles;
	return 0;
}
