#include "store.h"
#include "product.h"

// #include <cctype>
#include <iostream>
#include <vector>
#include <string> // string, stol
#include <algorithm> // find_if, min
#include <sstream> // istringstream
#include <unordered_set>
#include <map>

// a binary to unary tool for std::find_if
template <typename T>
struct ptrEqual {
	T* _other;
	ptrEqual(T* other) : _other(other) {}
	bool operator()(T*& current) const {
		return (*current == *_other);
	}
};

// predicate for unordered_set
template <typename T>
struct binaryPtrEqual {
	bool operator()(T* const& left, T* const& right) const {
		return (*left == *right);
	}
};

class DistGroup {
	private:
		unordered_set<Store*, hash<Store*>, binaryPtrEqual<Store>> _stores;
		unordered_set<Product*, hash<Product*>, binaryPtrEqual<Product>> _products;
	public:
		DistGroup(Product* prodPtr, Store* storePtr) {
			_products.insert(prodPtr);
			_stores.insert(storePtr);
		}

		// contruct group from single product via the edges
		DistGroup(Product* prodPtr) {
			_products.insert(prodPtr);
			addStoresFromProd(prodPtr);
		}

		// contruct group from single store via the edges
		DistGroup(Store* storePtr) {
			_stores.insert(storePtr);
			addProdsFromStore(storePtr);
		}

		long getSize() { return _stores.size() + _products.size(); }

		void insertProd(Product* prodPtr) { _products.insert(prodPtr); }

		void insertStore(Store* storePtr) { _stores.insert(storePtr); }

		bool hasProd(Product* prodPtr) {
			return (_products.find(prodPtr) != _products.end());
		}

		bool hasStore(Store* storePtr) {
			return (_stores.find(storePtr) != _stores.end());
		}

		void addStoresFromProd(Product* prodPtr) {
			vector<Store*> storesToAdd;
			prodPtr->appendAllMappedStores(storesToAdd);
			for (vector<Store*>::iterator it = storesToAdd.begin(); 
			it != storesToAdd.end(); ++it) {
				if (_stores.insert(*it).second)
					addProdsFromStore(*it);
			}
		}

		void addProdsFromStore(Store* storePtr) {
			vector<Product*> prodsToAdd;
			storePtr->appendAllMappedProds(prodsToAdd);
			for (vector<Product*>::iterator it = prodsToAdd.begin(); 
			it != prodsToAdd.end(); ++it) {
				if (_products.insert(*it).second)
					addStoresFromProd(*it);
			}
		}

		void appendGroup(DistGroup* other, long newGroupID) {
			for (auto it = other->_stores.begin(); it != other->_stores.end(); ++it) {
				(*it)->setGroup(newGroupID);
				_stores.insert(*it);
			}
			for (auto it = other->_products.begin(); it != other->_products.end(); ++it) {
				(*it)->setGroup(newGroupID);
				_products.insert(*it);
			}
		}

		// removes stores and products belonging to the other distribution
		// group and update them with their new group id
		void removeGroup(DistGroup* other, long newGroupID) {
			for (auto it = other->_stores.begin(); it != other->_stores.end(); ++it) {
				(*it)->setGroup(newGroupID);
				_stores.erase(*it);
			}
			for (auto it = other->_products.begin(); it != other->_products.end(); ++it) {
				(*it)->setGroup(newGroupID);
				_products.erase(*it);
			}
		}
};

class DistributionSystem {
	private:
		vector<Store*> _allStores;
		vector<Product*> _allProducts;
		map<long,DistGroup*> _groups;
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
				long groupID = getNextGroupID();
				storePtr->setGroup(groupID);
				DistGroup* group = new DistGroup(storePtr);
				_groups.emplace(groupID, group);

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
				long groupID = getNextGroupID();
				prodPtr->setGroup(groupID);
				DistGroup* group = new DistGroup(prodPtr);
				_groups.emplace(groupID, group);

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
				long groupID = (*found)->getGroup();
				DistGroup* group = _groups.find(groupID)->second;
				delete group;
				_groups.erase(groupID);

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
				long groupID = (*found)->getGroup();
				DistGroup* group = _groups.find(groupID)->second;
				delete group;
				_groups.erase(groupID);

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
				long groupID = (*found)->getGroup();
				DistGroup* group = _groups.find(groupID)->second;
				delete group;
				_groups.erase(groupID);

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
				long groupID = (*found)->getGroup();
				DistGroup* group = _groups.find(groupID)->second;
				delete group;
				_groups.erase(groupID);

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
				setGroupID(*prodFound, *storeFound);
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

				DistGroup* currentGroup = (_groups.find((*prodFound)->getGroup()))->second;
				// construct group from the store
				DistGroup* newGroup = new DistGroup(*storeFound);
				if (newGroup->hasProd(*prodFound)) { // if they are still connected
					delete newGroup;
				}
				else {
					long newGroupID = getNextGroupID();
					currentGroup->removeGroup(newGroup, newGroupID);
					_groups.emplace(newGroupID, newGroup);
				}

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

		bool handleCommand(string command) {
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
			else if (type == "?groups") {
				printGroups();
				return true;
			}
			return false;
		}

		void printGroups() {
			cout <<  _groups.size() << " distribution group(s)\n";
		}

		long getNextGroupID() {
			auto largest = _groups.rbegin();
			if (largest != _groups.rend()) // if non-empty
				return (largest->first + 1);
			else
				return 1;
		}

		void setGroupID(Product* prodPtr, Store* storePtr) {
			long prodGroupID = prodPtr->getGroup();
			long storeGroupID = storePtr->getGroup();
			DistGroup* storeGroupFound = _groups.find(storeGroupID)->second;
			DistGroup* prodGroupFound = _groups.find(prodGroupID)->second;
			if (prodGroupID == storeGroupID) {
				return;
			}
			// if they belong to different groups, merge the two groups and
			// label it with the minimum of the two group ids
			else if (prodGroupFound->getSize() < storeGroupFound->getSize()) {
				storeGroupFound->appendGroup(prodGroupFound, storeGroupID);
				_groups.erase(prodGroupID);
				delete prodGroupFound;
			}
			else {
				prodGroupFound->appendGroup(storeGroupFound, prodGroupID);
				_groups.erase(storeGroupID);
				delete storeGroupFound;
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
	bool groupsQueried = false;

	DistributionSystem sys(maxStores);

	while (getline(cin, command)) {
		groupsQueried = sys.handleCommand(command)|| groupsQueried;
	}

	if (!groupsQueried)
		sys.printAll();

	return 0;
}
