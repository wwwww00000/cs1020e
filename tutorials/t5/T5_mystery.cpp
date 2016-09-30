#include <iostream>
using namespace std;

template <typename T>
class LinkedList {

	struct DListNode {
		T element;
		DListNode* prev;
		DListNode* next;
	};

	// attributes of LinkedList<T> class
	DListNode* head;
	DListNode* tail;
	int numNodes;
	public:

	// 1.i. this class implements the iterator of the linked list
	class GuessWhatThisIs {
		friend class LinkedList;
		DListNode* pointsHere;
		GuessWhatThisIs(DListNode* node) : pointsHere(node) {} // private ctor
		public:
		GuessWhatThisIs& operator++(){ // for ++what
			pointsHere = pointsHere->next;
			return *this;
		}
		GuessWhatThisIs operator++(int){ // for what++
			GuessWhatThisIs oldValue = *this;
			++(*this);
			return oldValue;
		}
		GuessWhatThisIs& operator--(){ // for --what
			pointsHere = pointsHere->prev;
			return *this;
		}
		GuessWhatThisIs operator--(int){ // for what--
			GuessWhatThisIs oldValue = *this;
			--(*this);
			return oldValue;
		}
		T& operator*() { return pointsHere->element; } // for *what
		T* operator->() { return &pointsHere->element; } // for what->bleh
		bool operator==(const GuessWhatThisIs& other) { return pointsHere == other.pointsHere; }
		bool operator!=(const GuessWhatThisIs& other) { return !(*this == other); }
	};

	// ctor and dtor
	//	a real linked list will have copy constructor
	//	and will also overload the operator=()
	LinkedList() : numNodes(0) {
		head = new DListNode;
		head->prev = NULL;
		head->next = NULL;
		tail = head; // tail will always point to dummy node
	}
	~LinkedList() {
		for (DListNode* curr = head->next; curr != NULL; curr = curr->next)
			delete curr->prev; // destroy first node to node before dummy
		delete tail; // destroy dummy node
	}

	// methods
	// checks if list is empty
	bool mysteryA() { return numNodes == 0; }
	// returns the size of the list
	int mysteryB() { return numNodes; }
	// returns the first value of the list
	T& mysteryC() { return head->element; }
	// returns the last value of the list
	T& mysteryD() { return tail->prev->element; }
	// inserts an element at the front of the list
	void mysteryE(T& elm) {
		++numNodes;
		head = new DListNode {elm, NULL, head};
		head->next->prev = head; // go forward to the 2nd node and point backward to head
	}
	// inserts an element at the back of the list
	void mysteryF(T& elm) {
		++numNodes;
		tail->prev = new DListNode {elm, tail->prev, tail};
		if (tail->prev->prev == NULL) // previously only 1 node
			head = tail->prev;
		else //go backward 2 nodes and point it forward correctly
			tail->prev->prev->next = tail->prev;
	}
	// pops off the element at the front of the list
	void mysteryG() {
		--numNodes;
		DListNode* toRemove = head;
		head = head->next;
		head->prev = NULL;
		delete toRemove;
	}
	// pops off the element at the back of the list
	void mysteryH() {
		--numNodes;
		DListNode* toRemove = tail->prev;
		tail->prev = toRemove->prev;
		if (toRemove->prev == NULL)
			head = tail;
		else
			toRemove->prev->next = tail;
		delete toRemove;
	}

	// more methods
	// returns in iterator to the first node
	GuessWhatThisIs mysteryI() { return GuessWhatThisIs(head); }
	// returns in iterator to the last node
	GuessWhatThisIs mysteryJ() { return GuessWhatThisIs(tail); }
	// inserts a node before the current iterator and returns an iterator to
	// the newly inserted element
	GuessWhatThisIs mysteryK(GuessWhatThisIs what, T& elm) {
		++numNodes;
		DListNode* newNode = new DListNode {elm, what.pointsHere->prev, what.pointsHere};
		newNode->next->prev = newNode;
		if (newNode->prev == NULL)
			head = newNode;
		else
			newNode->prev->next = newNode;
		return --what; // return iterator to new elm
	}
	// removes the node at the current iterator and returns an iterator to
	// the node after the deleted node
	GuessWhatThisIs mysteryL(GuessWhatThisIs what) {
		--numNodes;
		DListNode* toRemove = what.pointsHere;
		++what; // return iterator to one after deleted elm
		if (toRemove->prev == NULL)
			head = toRemove->next;
		else
			toRemove->prev->next = toRemove->next;
		toRemove->next->prev = toRemove->prev;
		delete toRemove;
		return what;
	}

	// this method is to let you debug while playing around
	void println() {
		cout << numNodes << ": fwd[";
		if (head != tail) {
			cout << head->element;
			for (DListNode* curr = head->next; curr != tail; curr = curr->next)
				cout << ", " << curr->element;
		}
		cout << "] bwd[";
		if (head != tail) {
			cout << tail->prev->element;
			for (DListNode* curr = tail->prev->prev; curr != NULL; curr = curr->prev)
				cout << ", " << curr->element;
		}
		cout << "]" << endl;
	}

	// ignore these unless you are particularly interested. overloads for rvalue references
	void mysteryE(T&& elm) {
		T& ref = elm;
		mysteryE(elm);
	}
	void mysteryF(T&& elm) {
		T& ref = elm;
		mysteryF(elm);
	}
	GuessWhatThisIs mysteryK(GuessWhatThisIs what, T&& elm) {
		T& ref = elm;
		mysteryK(what, elm);
	}

	// other methods, for qn2, if you are interested
	
	// 2. appends all elements of other to this list
	void merge(LinkedList<T>& other) {} /* UNDONE */

	// inserts or deletes elements until the list if of size newSize. removes
	// extra elements or inserts value-initialized elements to make the size.
	void resize(int newSize) {} /* UNDONE */

	// reverses order of elements of the list. in a doubly linked
	// implementation. this can be achieved by setting the head to the tail and
	// iterating through all the nodes, swapping next with prev
	void reverse() {} /* UNDONE */

	// inserts all the nodes from the linked list other at the position pointed
	// to by what
	void splice(GuessWhatThisIs what, LinkedList<T>& other) {} /* UNDONE */
	void splice(GuessWhatThisIs what, LinkedList<T>& other,
			GuessWhatThisIs whaat, GuessWhatThisIs whaaat) {} /* UNDONE */

	// ignore these. overloads for rvalue references done
	void merge(LinkedList<T>&& other) {
		LinkedList<T>& ref = other;
		merge(ref);
	}
	void splice(GuessWhatThisIs what, LinkedList<T>&& other) {
		LinkedList<T>& ref = other;
		splice(what, ref);
	}
	void splice(GuessWhatThisIs what, LinkedList<T>&& other,
			GuessWhatThisIs whaat, GuessWhatThisIs whaaat) {
		LinkedList<T>& ref = other;
		splice(what, ref, whaat, whaaat);
	}
};

int main() {
	LinkedList<char> list;
	list.println();
	cout << list.mysteryB() << " " << (list.mysteryA() ? "true" : "false") <<  endl;
	list.mysteryE('0'); list.mysteryE('1');
	list.mysteryF('2'); list.mysteryF('0'); list.mysteryF('e');
	list.mysteryE('s'); list.mysteryE('c');
	list.println();
	cout << list.mysteryB() << " " << (list.mysteryA() ? "true" : "false") <<  endl;
	cout << list.mysteryC() << " " << list.mysteryD() << endl;

	list.mysteryL(--list.mysteryJ());
	string text = "ours";
	LinkedList<char>::GuessWhatThisIs what = ++list.mysteryI();
	for (int i = 0; i < text.length(); i++)
		list.mysteryK(what, text.at(i));
	*(what++) = 'e';
	list.mysteryK(what, ' ');
	list.println();

	return 0;
}
