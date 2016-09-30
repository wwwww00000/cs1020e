#include <iostream>
using namespace std;

int main() {
	// (a)
	//int i = 3;
	//cout << &i;
	
	// (b)
	//int* p = new int(3);
	//cout << &p << p;
	
	// (c)
	//int* ap = new int[3];
	//for (int i = 0; i < 3; i++)
		//ap[i] = i - 1;
	//cout << &ap << ap << *ap << ap[0];

	// (d)
	//int i = 3;
	//cout << *&i;

	// (e)
	//int* p = new int(3);
	//cout << *&p << &*p << **&p;
	
	// (f)
	//int** dp = new int* [3];
	//for (int i = 0; i < 3; i++)
		//dp[i] = new int(i-1);
	//cout << &dp << dp << *dp << dp[0] << **dp << *dp[0];
	
	// (g)
	int* p = new int (3);
	int** dp = &p;
	int*** tp = &dp;
	cout << *tp << endl << &**tp << endl << *&*tp << endl << **&tp << endl ;
}
