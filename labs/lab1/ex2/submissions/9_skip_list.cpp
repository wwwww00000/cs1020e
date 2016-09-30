#include <iostream>
#include <math.h>
using namespace std;

class Node {
	friend class SkipList;
	private:
		int _id; // numbering of person
		int _level;
		int _forward_skip; // number of nodes that a higher level node skips over
		Node* _next;
		Node* _upper;
		Node* _lower;
	public:
		Node(int id, int level, int forward_skip): 
			_id(id), _level(level), _forward_skip(forward_skip),
			_next(NULL), _upper(NULL), _lower(NULL) {
		}
};

// a circular, singly-linked skip list.
class SkipList {
	private:
		Node** _heads; // array of the first element of each list-layer
		Node** _tails; // array of the last element of each list-layer
		const int _num_levels;
		const int _initial_people;
		int _people_left;
		Node** _iterators; // array of the iterators for traversing the list
		int* _iterator_lag; // distance that higher level iterators are lagging behind
	public:
		SkipList(int N): _num_levels(log2(N)), _initial_people(N), _people_left(N) {
			_heads = new Node* [_num_levels];
			_tails = new Node* [_num_levels];
			_iterators = new Node* [_num_levels];
			_iterator_lag = new int [_num_levels];

			// initialization of heads of all levels
			for (int level = 0; level < _num_levels; level++) {
				_heads[level] = new Node(0, level, pow(2,level)); // first node
				if (level > 0) {
				_heads[level]->_lower = _heads[level-1];
				_heads[level-1]->_upper = _heads[level];
				}
			}
			// initialize tails and iterators to the starting elements
			for (int level = 0; level < _num_levels; level++) {
				_tails[level] = _heads[level];
				_iterators[level] = _heads[level];
			}

			// initalize the rest of the layers from the bottom up
			for (int id = 1; id < _people_left; id++) {
				Node* next_node = new Node(id, 0, 1);
				// connect new node to last node
				_tails[0]->_next = next_node;
				_tails[0] = next_node;

				// constructs higher levelled nodes. level N has a skip of log2(N).
				for (int level = 1; level < _num_levels; level++) {
					int forward_skip = pow(2,level);
					if (id % forward_skip != 0) {
						break;
					}
					else {
						Node* upper_node = new Node(id, level, forward_skip);
						// connect new node to last node
						_tails[level]->_next = upper_node;
						_tails[level] = upper_node;
						// connect new node to lower node
						_tails[level-1]->_upper = upper_node;
						upper_node->_lower = _tails[level-1];
					}
				}
			}

			// clean up loose ends and close circle
			for (int level = 0; level < _num_levels; level++) {
				_tails[level]->_forward_skip = _people_left - _tails[level]->_id;
				_tails[level]->_next = _heads[level];
			}
		}

		~SkipList() {
			for (int i = 0; i < _num_levels; i++) {
				int num_dead = _initial_people - _people_left;
				Node* current_node = _heads[i]; 
				for (int j = 0; j < _initial_people / pow(2,i) - num_dead; j++) {
					Node* next_node = current_node->_next;
					delete current_node;
					current_node = next_node;
				}
			}
			delete [] _heads;
			delete [] _tails;
			delete [] _iterators;
			delete [] _iterator_lag;
		}

		// advances the current iterator to one position before the person to
		// be removed.
		void advance(int n) {
			int steps_left = (n + _iterator_lag[_num_levels-1] - 1) % _people_left; 
			int	level = _num_levels - 1;

			// reset iterator lags
			for (int i = 0; i < _num_levels; i++) {
				_iterator_lag[i] = 0;
			}

			do {
				// take the skips if they don't overshoot
				while (steps_left >= _iterators[level]->_forward_skip) {
					steps_left -= _iterators[level]->_forward_skip;
					for (int i = level + 1; i < _num_levels; i++) {
						_iterator_lag[i] += _iterators[level]->_forward_skip;
					}
					_iterators[level] = _iterators[level]->_next;
				}
				// set all lower levelled nodes to the current position
				for (int lower = level-1; lower >= 0; lower--) {
					_iterators[lower] = _iterators[lower+1]->_lower;
				}
				level--;
			} while (steps_left > 0); 
		}

		// delete the node after the one currently pointed to by level 0 of the
		// iterator.
		void erase_after() {
			Node* next_node;

			// update and remove higher order nodes
			for (int level = 1; level < _num_levels; level++) {
				_iterator_lag[level] += 1;

				// update forward skips
				if (_iterator_lag[level] < _iterators[level]->_forward_skip) {
					_iterators[level]->_forward_skip -= 1;
				}
				else {
					next_node = _iterators[level]->_next;	
					_iterators[level]->_forward_skip += next_node->_forward_skip - 1;

					// delete the higher level node
					_iterators[level]->_next = next_node->_next;
					// replace head if necessary
					if (_iterators[level]->_id > next_node->_id)
						_heads[0] = next_node->_next;
					delete next_node;
				}
			}

			// delete level 0 node
			next_node = _iterators[0]->_next;
			_iterators[0]->_next = next_node->_next;
			// replace head if necessary
			if (_iterators[0]->_id > next_node->_id)
				_heads[0] = next_node->_next;
			_iterators[0] = next_node->_next;
			delete next_node;
			_people_left--;
		}

		// display the lowest level in the desired format
		void print_result() {
			Node* node = _heads[0];
			cout << "[";
			for (int i = 0; i < _people_left; i++) {
				cout << node->_id;
				if (i < _people_left - 1)
					cout << " ";
				node = node->_next;
			}
			cout << "]\n";
		}

		// prints state of all levels for debug purposes
		void print_all() {
			for (int level = 0; level < _num_levels; level++) {
				int num_dead = _initial_people - _people_left;
				Node* node = _heads[level];
				for (int i = 0; i < _initial_people / pow(2,level) - num_dead; i++) {
					cout << node->_id << " ";
					node = node->_next;
				}
				cout << "\n";
			}
		}

		// debug utility
		void print_iterators() {
			cout << "iterators: \n";
			for (int level = 0; level < _num_levels; level++) {
				cout << _iterators[level]->_id << " ";
			}
			cout << "\n";
		}

		// debug utility
		void print_iterator_lag() {
			cout << "iterator_lag: \n";
			for (int level = 0; level < _num_levels; level++) {
				cout << _iterator_lag[level] << " ";
			}
			cout << "\n";
		}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	long jumps;

	// read input
	cin >> N;

	SkipList people(N);	

	while (cin >> jumps) {
		people.advance(jumps);
		people.erase_after();
	}

	// display operation
	people.print_result();
	
	return 0;
}
