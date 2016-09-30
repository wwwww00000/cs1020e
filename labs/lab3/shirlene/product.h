#ifndef PRODUCT_H
	// will not enter if this file has already been visited

#define PRODUCT_H
#include "store.h"
	// visit store first, if store not already visited

#include <string>
using namespace std;

class Store; // forward declaration
	// If store is visited first, then Store class has not yet been declared

class Product {
	long _id;
	string _brand;
	string _name;
	Store** _stores;
	long _numStores;
	long _numMaxStores;
  public:
	Product(long id, string brand, string name, long maxStores);
	~Product();
	bool operator==(const Product& other);
	long getStoreCount();
	void addStore(Store* store);
	bool hasStore(Store* store);
	void eraseStore(Store* store);
	string toShortString();
	string toLongString();
};

#endif
