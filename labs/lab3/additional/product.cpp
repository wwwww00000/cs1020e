#include "product.h"
	// know how Product class is defined
#include <sstream>
#include <vector>

/* Attributes
long _id;
string _brand;
string _name;
Store** _stores;
long _numStores;
long _numMaxStores;
long _group;
*/

Product::Product(long id, string brand, string name, long maxStores) {
	_id = id;
	_brand = brand;
	_name = name;
	_numMaxStores = maxStores;
	_numStores = 0;
	_stores = new Store* [_numMaxStores];
	_group = 0;
}
Product::~Product() {
	delete [] _stores;
}

bool Product::operator==(const Product& other) { 
	return ((_id == other._id) || (_name == other._name && _brand == other._brand));
}

long Product::getStoreCount() {
	return _numStores;
}

void Product::addStore(Store* store) {
	_stores[_numStores] = store;
	++_numStores;
}

bool Product::hasStore(Store* store) {
	bool found = false;
	for (long i = 0; i < _numStores; i++) {
		if (*_stores[i] == *store) {
			found = true;
			break;
		}
	}
	return found;
}

void Product::eraseStore(Store* store) {
	for (long i = 0; i < _numStores; i++) {
		if (*_stores[i] == *store) {
			for (long j = i; j < _numStores-1; j++) { // shift subsequent elements up
				_stores[j] = _stores[j+1];
			}
			_stores[_numStores-1] = NULL;
			--_numStores;
			return;
		}
	}
}

// no trailing line break
string Product::toShortString() {
	ostringstream os;
	os << "-" << _id << " " << _brand << " " << _name << "-";
	return os.str();
}

string Product::toLongString() {
	ostringstream os;
	os << "=Product " << toShortString() << "\n";
	long s = getStoreCount();
	if (s != 0) {
		os << "=" << s << " store(s) [\n";
		for (long i = 0; i < s; i++)
			os << "=    " << _stores[i]->toShortString() << "\n";
		os << "=]\n";
	}
	else {
		os << "=" << s << " store(s)\n";
	}
	return os.str();
}

void Product::appendAllMappedStores(vector<Store*>& someStores) {
	someStores.insert(someStores.end(), _stores, _stores + _numStores);
}

void Product::setGroup(long group) {
	_group = group;
}

long Product::getGroup() {
	return _group;
}
