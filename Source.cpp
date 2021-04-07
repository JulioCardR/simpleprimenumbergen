#include <iostream>

using namespace std;

bool CheckPrime(int n);

void main() {
	int n = 1;
	int c = 1;
	while (true) {
		//cout << "checking " << n << endl;
		if (CheckPrime(n)) {
			cout << "prime " << c << ": " << n << endl;
			c++;
		}
		n++;
	}
}

bool CheckPrime(int n) {
	int h = (n / 2) + 1;
	//cout << "h is " << h << endl;
	for (int i = 1; i < h; i++) {
	//	cout << "i is " << i << endl;
		if (n == 1) {
			return true;
		}
		if (n % i == 0 && i != 1) {
			return false;
		}
	}
	//system("pause");
	return true;
}