#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <set>
#include <sstream>
using namespace std;

enum Side { up, down, left, right };
typedef pair<long,long> Segment;

// A set of non-overlapping, possibly disjoint segments
class Interval {
	private:
		set<long> _segments;
		// set<int> _seg_starts;
		// set<int> _seg_ends;
	public:
		// the symmetric difference of two sets of intervals is their union
		// minus their intersection. will mutate.
		void symmetric_difference(Interval other) {
			for (set<long>::iterator it = other._segments.begin(); it !=
				other._segments.end(); ++it) {
				set<long>::iterator found = _segments.find(*it);
				if (found != _segments.end())
					_segments.erase(found);
				else
					_segments.insert(*it);
			}
		}

		// overloaded for operation with single segment. will mutate.
		void symmetric_difference(Segment seg) {
			set<long>::iterator seg_start = _segments.find(seg.first);
			set<long>::iterator seg_end = _segments.find(seg.second);
			if (seg_start != _segments.end()) // if point is found
				_segments.erase(seg_start);
			else 
				_segments.insert(seg.first);
			if (seg_end != _segments.end()) // if point is found
				_segments.erase(seg_end);
			else 
				_segments.insert(seg.second);
		}

		long count_intervals() {
			return _segments.size() / 2;
		}

		bool equal_to(Interval other) {
			return (_segments == other._segments);
		}

		// void union_with(Segment seg) {
			// auto end_join = _seg_starts.find(seg.second);
			// auto start_join = _seg_ends.find(seg.first);
			// if (end_join != _seg_starts.end() && start_join != _seg_ends.end()) {
				// _seg_starts.erase(end_join);
				// _seg_ends.erase(start_join);
				// --_num_seg;
			// }
			// else if (end_join != _seg_starts.end() && start_join == _seg_ends.end()) {
				// _seg_starts.erase(end_join);
				// _seg_starts.insert(seg.first);
			// }
			// else if (end_join == _seg_starts.end() && start_join != _seg_ends.end()) {
				// _seg_ends.erase(start_join);
				// _seg_ends.insert(seg.second);
			// }
			// else {
				// _seg_starts.insert(seg.first);
				// _seg_ends.insert(seg.second);
				// ++_num_seg;
			// }
		// }
};


class Rectangle {
	private:
		long _left;
		long _right;
		long _up;
		long _down;
	public:
		Rectangle(long x1, long y1, long x2, long y2) {
			_left = min(x1, x2); 
			_right = max(x1, x2);
			_down = min(y1, y2);
			_up = max(y1, y2);
		}

		long get_side(Side side) {
			switch(side) {
				case Side::up: return _up;
				case Side::down: return _down;
				case Side::left: return _left;
				case Side::right: return _right;
				default: return _left; // for compiler pedantry
			}
		}

		// returns the vertical line segment of the rectangle
		Segment get_segment() {
			return make_pair(_down, _up);
		}
};

// a line sweep algorithm implementation
long count_combined_rectangles(Rectangle** rectangles, long num_rects) {
	// hash map of rectangles by their start and end points
 	unordered_multimap<long,Rectangle*> rects_by_endpoints; 
	// set of horizontal coordinates where rectangles begin or end
	set<int> events;
	long count = 0;

	for (int i = 0; i < num_rects; ++i) {
		rects_by_endpoints.insert(make_pair(rectangles[i]->get_side(Side::left),
			rectangles[i]));
		rects_by_endpoints.insert(make_pair(rectangles[i]->get_side(Side::right),
			rectangles[i]));
		events.insert(rectangles[i]->get_side(Side::left));
		events.insert(rectangles[i]->get_side(Side::right));
	}
	
	// compute the union of all intervals for the first event coordinate
	set<int>::iterator event_it = events.begin();
	auto rects_involved = rects_by_endpoints.equal_range(*event_it);
	Interval previous;
	for (auto rect_it = rects_involved.first; rect_it !=
		rects_involved.second; ++rect_it) {
		previous.symmetric_difference((rect_it->second)->get_segment());
	}

	// sweep through all horizontal coordinates with events
	while (event_it != events.end()) { 
		Interval current;
		// rectangles involved at the current line coordinate
		rects_involved = rects_by_endpoints.equal_range(*event_it);
		for (auto rect_it = rects_involved.first; rect_it !=
			rects_involved.second; ++rect_it) {
			current.symmetric_difference((rect_it->second)->get_segment());
		}
		current.symmetric_difference(previous);
		if (!current.equal_to(previous)) {
			count += previous.count_intervals();
			previous = current;
		}
		++event_it;
	}
	// unordered_multimap<long,Rectangle*> ends;
	// for (int i = 0; i < num_rects; ++i) {
		// starts.insert(make_pair(rectangles[i]->get_side(Side::left),
			// rectangles[i]));
		// ends.insert(make_pair(rectangles[i]->get_side(Side::right),
			// rectangles[i]));
		// events.insert(rectangles[i]->get_side(Side::left));
		// events.insert(rectangles[i]->get_side(Side::right));
	// }
	
	// set<int>::iterator event_it = events.begin();
	// while (event_it != events.end()) {
		// auto start_range = starts.equal_range(*event_it);
		// for (auto start_it = start_range.first; start_it != start_range.second;
			// ++start_it) {
			
		// }
		// auto end_range = ends.equal_range(*event_it);
		// for (auto end_it = end_range.first; end_it != end_range.second;
			// ++end_it) {
		// }

		// ++event_it;
	// }
	return count;
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
	
	long combined_rects = count_combined_rectangles(rectangles, num_rects); // perform operation
	
	for (long idx = 0; idx < num_rects; idx++) {
		delete rectangles[idx];
	}
	cout << num_rects << "\n"; // output result
	
	delete [] rectangles;
	return 0;
}
