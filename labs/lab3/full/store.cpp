#include "store.h"
	// know how Store class is defined
#include <sstream>
#include <algorithm> // find

/* Attributes
long _id;
string _outlet;
string _name;
vector<Product*> _products;
*/

Store::Store(long id, string outlet, string name) {
	_id = id;
	_outlet = outlet;
	_name = name;
}

Store::~Store() {}

bool Store::operator==(const Store& other) {
	return ((_id == other._id) || (_name == other._name && _outlet == other._outlet));
}

long Store::getProductCount() { return _products.size(); }

void Store::addProduct(Product* prod) { 
	_products.push_back(prod);
}

bool Store::hasProduct(Product* prod) {
	return (find(_products.begin(), _products.end(), prod) != _products.end());
}

// runtime error if product does not exist
void Store::eraseProduct(Product* prod) { 
	vector<Product*>::iterator remove = find(_products.begin(), _products.end(), prod);
	_products.erase(remove);
}

// no trailing line break
string Store::toShortString() {
	ostringstream os;
	os << "-" << _id << " " << _outlet << " " << _name << "-";
	return os.str();
}

string Store::toLongString() {
	ostringstream os;
	os << "=Store " << toShortString() << "\n";
	long p = getProductCount();
	if (p != 0) {
		os << "=" << p << " product(s) [\n";
		for (long i = 0; i < p; i++)
			os << "=    " << _products[i]->toShortString() << "\n";
		os << "=]\n";
	}
	else {
		os << "=" << p << " product(s)\n";
	}
	return os.str();
}
