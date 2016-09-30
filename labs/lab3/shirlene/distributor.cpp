#include "store.h"
#include "product.h"
#include <cctype>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class DistributionSystem {
	vector<Store*> _allStores;
	vector<Product*> _allProducts;
	long _maxStores;
	public:
	DistributionSystem(long maxStores)
		: _allStores(), _allProducts(), _maxStores(maxStores) {}
	~DistributionSystem() {
		for (vector<Store*>::iterator iter = _allStores.begin();
				iter!=_allStores.end(); iter++) {
			delete *iter;
		}
		for (vector<Product*>::iterator iter = _allProducts.begin();
				iter!=_allProducts.end(); iter++) {
			delete *iter;
		}
	}

	string addStore(long id, string outlet, string storeName) { 
		ostringstream os;
		Store* newStore = new Store(id, outlet, storeName);
		os << "Store " << newStore->toShortString() << " added\n";
		_allStores.push_back(newStore);
		return os.str();	
	}


	string addProduct(long id, string brand, string prodName) { 
		ostringstream os;
		Product* newProd = new Product(id, brand, prodName, _maxStores);
		os << "Product " << newProd->toShortString() << " added\n";
		_allProducts.push_back(newProd);
		return os.str();	
	}

	string removeStore(long id) {
		ostringstream os;
		Store store = Store(id, "", "");
		vector<Store*>::iterator toRemove;
		for (vector<Store*>::iterator iter = _allStores.begin();
		iter!=_allStores.end(); iter++) {
			if (**iter == store) {
				os << "Store " << (*iter)->toShortString() << " removed\n";
				toRemove = iter;
			}
		}
		delete *toRemove;
		_allStores.erase(toRemove);
		return os.str();	
	}

	string removeStore(string outlet, string storeName) {
		ostringstream os;
		Store store = Store(0, outlet, storeName);
		vector<Store*>::iterator toRemove;
		for (vector<Store*>::iterator iter = _allStores.begin();
		iter!=_allStores.end(); iter++) {
			if (**iter == store) {
				os << "Store " << (*iter)->toShortString() << " removed\n";
				toRemove = iter;
			}
		}
		delete *toRemove;
		_allStores.erase(toRemove);
		return os.str();
	}

	string removeProduct(long id) {
		ostringstream os;
		Product product = Product(id, "", "", _maxStores);
		vector<Product*>::iterator toRemove;
		for (vector<Product*>::iterator iter = _allProducts.begin();
		iter!=_allProducts.end(); iter++) {
			if (**iter == product) {
				os << "Product " << (*iter)->toShortString() << " removed\n";
				toRemove = iter;
			}
		}
		delete *toRemove;
		_allProducts.erase(toRemove);
		return os.str();	
	}

	string removeProduct(string brand, string prodName) { 
		ostringstream os;
		Product product = Product(0, brand, prodName, _maxStores);
		vector<Product*>::iterator toRemove;
		for (vector<Product*>::iterator iter = _allProducts.begin();
		iter!=_allProducts.end(); iter++) {
			if (**iter == product) {	
				os << "Product " << (*iter)->toShortString() << " removed\n";
				toRemove = iter;
			}
		}
		delete *toRemove;
		_allProducts.erase(toRemove);
		return os.str();	
	}

	string map(string brand, string prodName, string outlet, string storeName) {
		ostringstream os;
		Product product = Product(0, brand, prodName, 0);
		Product* prodToMap;
		for (vector<Product*>::iterator iter = _allProducts.begin();
				iter!=_allProducts.end(); iter++) {
			if (**iter == product) {	
				prodToMap = *iter;
				// prodToMap->addStore(*storeToMap);
			}
		}
		Store store = Store(0, outlet, storeName);
		Store* storeToMap;
		for (vector<Store*>::iterator iter = _allStores.begin();
				iter!=_allStores.end(); iter++) {
			if (**iter == store) {	
				storeToMap = *iter;
			}
		}
		os << "Product " << prodToMap->toShortString() << " mapped to store " <<
			storeToMap->toShortString() << '\n';
		return os.str();	
	}

	string unmap(string brand, string prodName, string outlet, string storeName) {
		ostringstream os;
		Product product = Product(0, brand, prodName,0);
		Product* prodToMap;
		for (vector<Product*>::iterator iter = _allProducts.begin();
				iter!=_allProducts.end(); iter++) {
			if (**iter == product) {	
				prodToMap = *iter;
			}
		}
		Store store = Store(0, outlet, storeName);
		Store* storeToMap;
		for (vector<Store*>::iterator iter = _allStores.begin();
				iter!=_allStores.end(); iter++) {
			if (**iter == store) {	
				storeToMap = *iter;
			}
		}
		os << "Product " << prodToMap->toShortString() << " unmapped to store " <<
			storeToMap->toShortString() << '\n';
		return os.str();	
	}

	void printAll() { 
		cout << _allStores.size() << "store(s) remaining\n\n";
		for (vector<Store*>::iterator iter = _allStores.begin();
		iter!=_allStores.end(); iter++) {
			cout << (*iter)->toLongString() << "\n\n";
		}
		cout << _allProducts.size() << "product(s) remaining\n\n";
		for (vector<Product*>::iterator iter = _allProducts.begin();
		iter!=_allProducts.end(); iter++) {
			cout << (*iter)->toLongString() << "\n\n";
		}
	}
};

int main() {
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL);

	long maxStores;
	string word;

	cin >> maxStores;
	DistributionSystem sys(maxStores);
	string sentence;
	while (getline(cin, sentence)) {
		vector<string> words;
		istringstream iss(sentence);
		while (iss.good()) {
			iss >> word;
			words.push_back(word);
		}
		if (words[0] == "+store") {
			sys.addStore(stol(words[1]), words[2], words[3]);
		}
		else if (words[0] == "-store" && words.size()!=2) {
			sys.removeStore(words[1], words[2]);
		}
		else if (words[0] == "-store" && words.size()==2) {
			sys.removeStore(stol(words[1]));
		}
		else if (words[0] == "+prod") {
			sys.addProduct(stol(words[1]), words[2], words[3]);
		}
		else if (words[0] == "-prod" && words.size()!=2) {
			sys.removeProduct(words[1], words[2]);
		}
		else if (words[0] == "-prod" && words.size()==2) {
			sys.removeProduct(stol(words[1]));
		}
		else if (words[0] == "+map") {
			sys.map(words[1], words[2], words[3], words[4]);
		}
		else if (words[0] == "-map") {
			sys.unmap(words[1], words[2], words[3], words[4]);
		}
	}
	cout << '\n';
	sys.printAll();
	return 0;
}
