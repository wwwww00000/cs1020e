#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n, value;
	int count1 = 0;
	int count2 = 0;
	int array[1000000];

	cin >> n;
	for (int i=0; i<n; i++) {
		cin >> value;
		array[i] = value;
	}
	sort(array, array+n);
	
	if (n%2==1) { //for odd n
		cout << array[n/2] << ' '; 
	}
	else { // for even n
		cout << array[(n/2)-1] << ' ';
	}
	
	// count how many digits are in the array
	if (n%2==1) {
		for (int j=0; j<n; j++) {
			if (array[j]==array[n/2]) {
				++count1;
			}
		}
		cout << count1 << ' ';
	}
	else {
		for (int j=0; j<n; j++) {
			if (array[j]==array[(n/2)-1] || array[j]==array[(n/2)]) {
				++count1;
			}
		}
		cout << count1 << ' ';
	}

	if (n%2==1) {
		cout << "1\n";
	}
	else {
		if (array[n/2]==array[(n/2)-1]) {
			cout << "1\n";
		}
		else {
			int x = array[(n/2)-1];
			while (x<=array[(n/2)]) {
				++count2;
				if (x==array[(n/2)+1]) {
					break;
				}
				++x;
			}
			cout << count2 << '\n';
		}
	}

	return 0;
}





