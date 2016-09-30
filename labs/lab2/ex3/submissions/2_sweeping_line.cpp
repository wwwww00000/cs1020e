#include <iostream>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <iterator>
#include <set>
#include <sstream>
using namespace std;

enum Side { up, down, left, right };
typedef pair<long,long> Segment;

// A set of non-overlapping, possibly disjoint segments
class Interval {
	private:
		// one list of the beginnings and endings of the segments. this is
		// possible as they are disjoint.
		set<long> _segments;
	public:
		// the symmetric difference of two sets of intervals is their union
		// minus their intersection. will mutate.
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

		// overloaded for operation with Interval. will mutate.
		void symmetric_difference(Interval& other) {
			for (set<long>::iterator it = other._segments.begin(); it !=
				other._segments.end(); ++it) {
				set<long>::iterator found = _segments.find(*it);
				if (found != _segments.end())
					_segments.erase(found);
				else
					_segments.insert(*it);
			}
		}

		bool intersects_with(Interval other) {
			if (other.count_segments() == 0) // if other is empty
				return false;
			bool intersected = false;
			// start iterates through all the start points of the segments
			for (set<long>::iterator start = other._segments.begin(); (start !=
				other._segments.end() && !intersected); advance(start,2)) {

				// corresponding end point
				set<long>::iterator end = start; 
				++end;

				// if segment is outside of the intervals terminal points
				if (*start >= *_segments.rbegin() || *end <= *_segments.begin())
					continue;

				set<long>::iterator lower = _segments.lower_bound(*start);
				set<long>::iterator upper = _segments.lower_bound(*end);
				// if segment is wholly contained between two neighbouring
				// points of interval
				if (*lower == *upper) {
					// determine the parity of that point
					intersected = distance(_segments.begin(), lower) % 2;
				}
				// if segment contains one of the points of the interval
				else 
					intersected = true;
			}
			return intersected;
		}

		long count_segments() {
			return _segments.size() / 2;
		}
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
	// hash map of rectangles by their start and end points for fast access
 	unordered_multimap<long,Rectangle*> rects_starts; 
 	unordered_multimap<long,Rectangle*> rects_ends; 
	// set of horizontal coordinates where rectangles begin or end
	set<int> events;
	long count = 0;

	// populate hash maps and event coordinates
	for (int i = 0; i < num_rects; ++i) {
		rects_starts.insert(make_pair(rectangles[i]->get_side(Side::left),
			rectangles[i]));
		rects_ends.insert(make_pair(rectangles[i]->get_side(Side::right),
			rectangles[i]));
		events.insert(rectangles[i]->get_side(Side::left));
		events.insert(rectangles[i]->get_side(Side::right));
	}
	
	// compute the union of all intervals for the first event coordinate
	set<int>::iterator event_it = events.begin();
	auto rects_involved = rects_starts.equal_range(*event_it);
	Interval previous;
	for (auto rect_it = rects_involved.first; rect_it !=
		rects_involved.second; ++rect_it) {
		previous.symmetric_difference((rect_it->second)->get_segment());
	}
	++event_it;

	// sweep through all subsequent horizontal event coordinates
	while (event_it != events.end()) { 
		// build the union of intervals of rectangle beginnings
		Interval current_starts;
		auto starts_involved = rects_starts.equal_range(*event_it);
		for (auto rect_it = starts_involved.first; rect_it !=
			starts_involved.second; ++rect_it) {
			// the symmetric difference of disjoint sets is their union
			current_starts.symmetric_difference((rect_it->second)->get_segment());
		}

		// build the union of intervals of rectangle endings
		Interval current_ends;
		auto ends_involved = rects_ends.equal_range(*event_it);
		for (auto rect_it = ends_involved.first; rect_it !=
			ends_involved.second; ++rect_it) {
			current_ends.symmetric_difference((rect_it->second)->get_segment());
		}

		// merges starts and ends together if appropriate
		current_starts.symmetric_difference(current_ends);
		if (previous.intersects_with(current_starts)) { // if any rectangles have ended
			count += previous.count_segments();
		}
		// update the currently active intervals
		previous.symmetric_difference(current_starts);

		++event_it;
	}

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
	// each arr element is a pointer to a Rect object
	Rectangle** rectangles = new Rectangle* [num_rects]; 

	for (long i = 0; i < num_rects; i++) {
		rectangles[i] = new Rectangle(0, 0, 0, 0);
		cin >> *rectangles[i];
	} 
	
	long combined_rects = count_combined_rectangles(rectangles, num_rects);
	
	for (long idx = 0; idx < num_rects; idx++) {
		delete rectangles[idx];
	}
	cout << combined_rects << "\n"; // output result
	
	delete [] rectangles;
	return 0;
}
