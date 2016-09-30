#ifndef STORE_H
	// will not enter if this file has already been visited

#define STORE_H
#include "product.h"
	// visit product first, if product not already visited

#include <string>
#include <vector>
using namespace std;

class Product; // forward declaration
	// If product is visited first, then Product class has not yet been declared

class Store {
	long _id;
	string _outlet;
	string _name;
	vector<Product*> _products;
  public:
	Store(long id, string outlet, string name);
	~Store();
	bool operator==(const Store& other);
	long getProductCount();
	void addProduct(Product* prod);
	bool hasProduct(Product* prod);
	void eraseProduct(Product* prod);
	string toShortString();
	string toLongString();
};

#endif
