#include "product.h" // know how Product class is defined
#include <sstream>
using namespace std;

Product::Product(long id, string brand, string name, long maxStores) { 
	_id = id;
	_brand = brand;
	_name = name;
	_stores = new Store*[maxStores];
	_numStores = 0;
	_numMaxStores = maxStores;
}
Product::~Product() {
	delete [] _stores;
}

bool Product::operator==(const Product& other) { 
	if (_id == other._id || (_brand == other._brand && _name == other._name)) {
		return true;
	}
	return false;
}
long Product::getStoreCount() {
	return _numStores;;
}

void Product::addStore(Store* store) { 
	_stores[_numStores] = store;	
}
bool Product::hasStore(Store* store) {
	for (int i=0; i<_numMaxStores; i++) {
		if (*_stores[i] == *store) {
			return true;
		}
		return false;
	}
}

void Product::eraseStore(Store* store) { 
	for (int i=0; i<_numStores; i++) {
		if (*_stores[i] == *store) {
			for (int j=i+1; j<_numStores; j++) {
				_stores[j-1] = _stores[j];
			}
		}
	}
}

string Product::toShortString() { 
	ostringstream os;
	os << '-' << _id << " " << _brand << " " << _name << '-';
	return os.str();
}

string Product::toLongString() { 
	ostringstream os;
	os << '=' << "Products " << toShortString() << '\n' << '=' <<
		_numStores << " stores(s)";
	if (_numStores==0) {
		return os.str();
	}
	os << " [" << '\n' << "=    ";
		for (int i=0; i<_numStores; i++) {
			os << _stores[i]->toShortString() << '\n';
		}
	os << "=]";
	return os.str();
}



