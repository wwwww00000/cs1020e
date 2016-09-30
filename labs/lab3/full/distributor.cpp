#include "store.h"
#include "product.h"

// #include <cctype>
#include <iostream>
#include <vector>
#include <string> // string, stol
#include <algorithm> // find_if, min
#include <sstream> // istringstream

// a binary to unary tool for std::find_if
template <typename T>
struct ptrEqual {
	T* _other;
	ptrEqual(T* other) : _other(other) {}
	bool operator()(T*& current) const {
		return (*current == *_other);
	}
};


class DistributionSystem {
	private:
		vector<Store*> _allStores;
		vector<Product*> _allProducts;
		long _maxStores;
	public:
		DistributionSystem(long maxStores)
			: _allStores(), _allProducts(), _maxStores(maxStores) {}

		~DistributionSystem() {
			for (vector<Store*>::iterator it = _allStores.begin(); it !=
				_allStores.end(); ++it) delete *it;
			for (vector<Product*>::iterator it = _allProducts.begin(); it !=
				_allProducts.end(); ++it) delete *it;
		}

		void addStore(long id, string outlet, string storeName) {
			Store* storePtr = new Store(id, outlet, storeName);
			vector<Store*>::iterator found = find_if(_allStores.begin(),
				_allStores.end(), ptrEqual<Store>(storePtr));
			if (found == _allStores.end()) {
				_allStores.push_back(storePtr);
				cout << "Store " << storePtr->toShortString() << " added\n";
			}
			else {
				cout << "Store " << (*found)->toShortString() << 
					" already exists, cannot add " <<
					storePtr->toShortString() << "\n";
				delete storePtr;
			}
		}

		void addProduct(long id, string brand, string prodName) {
			Product* prodPtr = new Product(id, brand, prodName, _maxStores);
			vector<Product*>::iterator found = find_if(_allProducts.begin(),
				_allProducts.end(), ptrEqual<Product>(prodPtr));
			if (found == _allProducts.end()) {
				_allProducts.push_back(prodPtr);
				cout << "Product " << prodPtr->toShortString() << " added\n";
			}
			else {
				cout << "Product " << (*found)->toShortString() << 
					" already exists, cannot add " <<
					prodPtr->toShortString() << "\n";
				delete prodPtr;
			}
		}

		void removeStore(long id) {
			Store toFind(id, "", "");
			vector<Store*>::iterator found = find_if(_allStores.begin(),
				_allStores.end(), ptrEqual<Store>(&toFind));
			if (found == _allStores.end()) {
				cout << "No such store\n";
			}
			else if ((*found)->getProductCount() != 0) {
				cout << "Cannot remove, store " << (*found)->toShortString() <<
					" is mapped to product(s)\n";
			}
			else {
				cout << "Store " << (*found)->toShortString() << " removed\n";
				delete *found;
				_allStores.erase(found);
			}
		}

		void removeStore(string outlet, string storeName) {
			Store toFind(0, outlet, storeName);
			vector<Store*>::iterator found = find_if(_allStores.begin(),
				_allStores.end(), ptrEqual<Store>(&toFind));
			if (found == _allStores.end()) {
				cout << "No such store\n";
			}
			else if ((*found)->getProductCount() != 0) {
				cout << "Cannot remove, store " << (*found)->toShortString() <<
					" is mapped to product(s)\n";
			}
			else {
				cout << "Store " << (*found)->toShortString() << " removed\n";
				delete *found;
				_allStores.erase(found);
			}
		}

		void removeProduct(long id) {
			Product toFind(id, "", "", _maxStores);
			vector<Product*>::iterator found = find_if(_allProducts.begin(),
				_allProducts.end(), ptrEqual<Product>(&toFind));
			if (found == _allProducts.end()) {
				cout << "No such product\n";
			}
			else if ((*found)->getStoreCount() != 0) {
				cout << "Cannot remove, product " << (*found)->toShortString() <<
					" is mapped to store(s)\n";
			}
			else {
				cout << "Product " << (*found)->toShortString() << " removed\n";
				delete *found;
				_allProducts.erase(found);
			}
		}

		void removeProduct(string brand, string prodName) {
			Product toFind(0, brand, prodName, _maxStores);
			vector<Product*>::iterator found = find_if(_allProducts.begin(),
				_allProducts.end(), ptrEqual<Product>(&toFind));
			if (found == _allProducts.end()) {
				cout << "No such product\n";
			}
			else if ((*found)->getStoreCount() != 0) {
				cout << "Cannot remove, product " << (*found)->toShortString() <<
					" is mapped to store(s)\n";
			}
			else {
				cout << "Product " << (*found)->toShortString() << " removed\n";
				delete *found;
				_allProducts.erase(found);
			}
		}
		void addMap(string brand, string prodName, string outlet, string storeName) {
			Product prodToFind(0, brand, prodName, _maxStores);
			Store storeToFind(0, outlet, storeName);
			vector<Product*>::iterator prodFound = find_if(_allProducts.begin(),
				_allProducts.end(), ptrEqual<Product>(&prodToFind));
			vector<Store*>::iterator storeFound = find_if(_allStores.begin(),
				_allStores.end(), ptrEqual<Store>(&storeToFind));
			if (prodFound == _allProducts.end() || storeFound == _allStores.end()) {
				cout << "Cannot map, no such product or store\n";
			}
			else if ((*prodFound)->getStoreCount() == _maxStores) {
				cout << "Product " << (*prodFound)->toShortString() <<
					" maxed out, cannot map to store " <<
					(*storeFound)->toShortString() << "\n";
			}
			else if ((*storeFound)->hasProduct(*prodFound)) {
				cout << "Product " << (*prodFound)->toShortString() << 
					" already mapped to store " <<
					(*storeFound)->toShortString() << "\n";
			}
			else {
				(*prodFound)->addStore(*storeFound);
				(*storeFound)->addProduct(*prodFound);
				cout << "Product " << (*prodFound)->toShortString() << 
				" mapped to store " << (*storeFound)->toShortString() << "\n";
			}
		}

		void unmap(string brand, string prodName, string outlet, string storeName) {
			Product prodToFind(0, brand, prodName, _maxStores);
			Store storeToFind(0, outlet, storeName);
			vector<Product*>::iterator prodFound = find_if(_allProducts.begin(),
				_allProducts.end(), ptrEqual<Product>(&prodToFind));
			vector<Store*>::iterator storeFound = find_if(_allStores.begin(),
				_allStores.end(), ptrEqual<Store>(&storeToFind));
			if (prodFound == _allProducts.end() || storeFound == _allStores.end()) {
				cout << "Cannot unmap, no such product or store\n";
			}
			else if (!(*prodFound)->hasStore(*storeFound) || 
			!(*storeFound)->hasProduct(*prodFound)) {
				cout << "No existing mapping between product " <<
					(*prodFound)->toShortString() << " and store " << 
					(*storeFound)->toShortString() << "\n";
			}
			else {
				(*prodFound)->eraseStore(*storeFound);
				(*storeFound)->eraseProduct(*prodFound);
				cout << "Product " << (*prodFound)->toShortString() << 
				" unmapped from store " << (*storeFound)->toShortString() << "\n";
			}
		}

		void printAll() {
			long storesLeft = _allStores.size();
			long productsLeft = _allProducts.size();
			cout << "\n" << storesLeft << " store(s) remaining\n";
			for (long i = 0; i < storesLeft; ++i) {
				cout << "\n" << _allStores[i]->toLongString();
			}
			cout << "\n" << productsLeft << " product(s) remaining\n";
			for (long i = 0; i < productsLeft; ++i) {
				cout << "\n" << _allProducts[i]->toLongString();
			}
		}

		void handleCommand(string command) {
			istringstream iss(command);
			string type, arg;
			vector<string> args;
			iss >> type;
			while(iss >> arg) {
				args.push_back(arg);
			}
			if (type == "+store") {
				addStore(stol(args[0]), args[1], args[2]);
			}
			else if (type == "-store") {
				if (args.size() == 2)
					removeStore(args[0], args[1]);
				else
					removeStore(stol(args[0]));
			}
			else if (type == "+prod") {
				addProduct(stol(args[0]), args[1], args[2]);
			}
			else if (type == "-prod") {
				if (args.size() == 2)
					removeProduct(args[0], args[1]);
				else 
					removeProduct(stol(args[0]));
			}
			else if (type == "+map") {
				addMap(args[0], args[1], args[2], args[3]);
			}
			else if (type == "-map") {
				unmap(args[0], args[1], args[2], args[3]);
			}
		}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string command;
	long maxStores;

	getline(cin, command);
	istringstream iss(command);
	iss >> maxStores;

	DistributionSystem sys(maxStores);

	while (getline(cin, command)) {
		sys.handleCommand(command);
	}

	sys.printAll();

	return 0;
}
