#include "store.h" // know how Store class is defined
#include <sstream>
#include <vector>
using namespace std;

Store::Store(long id, string outlet, string name) { 
	_id = id;
	_outlet = outlet;
	_name = name;
}
Store::~Store() {}


bool Store::operator==(const Store& other) { 
	if (_id == other._id || (_outlet == other._outlet && _name == other._name) ) {
		return true;
	}
	return false;
}
long Store::getProductCount() { 
	return _products.size(); 
}

void Store::addProduct(Product* prod) {
	_products.push_back(prod);
}

bool Store::hasProduct(Product* prod) { 
	for (vector<Product*>::iterator iter = _products.begin();
	iter!=_products.end(); iter++) {
		if (**iter == *prod) {
			return true;
		}
	}
	return false;
}

void Store::eraseProduct(Product* prod) { 
	for (vector<Product*>::iterator iter = _products.begin();
	iter!=_products.end(); iter++) {
		if (**iter == *prod) {
			_products.erase(iter);
		}
	}
}
		
string Store::toShortString() { 
	ostringstream os;
	os << '-' << _id << " " << _outlet << " " << _name << '-';
	return os.str();
}

string Store::toLongString() { 
	ostringstream os;
	os << '=' << "Store " << toShortString() << '\n' << '=' << _products.size()
	<< " product(s)";
	if (_products.size()==0) {
		return os.str();
	}
	os << " [" << '\n' << "=    "; 
	for (int i=0; i<_products.size(); i++) {
		os << _products[i]->toShortString() << '\n';
	}
	os << "=]";
	return os.str();
}


