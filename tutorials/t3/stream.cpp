#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Product {
		long _productID;
		long _volume;
		long _weight;
	public:
		Product(string pInput) {
			vector<string> tokens;
			string token, delimeters = ",:;|# ";
			size_t position;
			while ((position = pInput.find_first_of(delimeters)) != string::npos) {
			// while (pInput != "") {
				token = pInput.substr(0, position);
				tokens.push_back(token);
				pInput.erase(0, position + 1);
			}
			tokens.push_back(pInput);
			long numTokens = tokens.size();
			_productID = stol(tokens[0]);
			_volume = stol(tokens[numTokens-2]);
			_weight = stol(tokens[numTokens-1]);
		}

		string str() {
			ostringstream os;
			os << "|" << setw(8) << _productID;
			os << "|" << setw(7) << _volume;
			os << "|" << setw(4) << _weight << "|";
			return os.str();
		}

		long getProductID() { return _productID; }
		long getVolume() { return _volume; }
		long getWeight() { return _weight; }
};

int main() {
	string productDesc = "1234567,ball,dirt|9000;50";
	Product product(productDesc);
	cout << product.str() << "\n";

	return 0;
}
