#include <iostream>
#include <string>

using namespace std;

int main() {

	// prompt user for integer
	// check that input is an integer
	// convert to string
	int x;
	cout << "Enter a number: ";
	cin >> x;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Bad entry. Enter a NUMBER: ";
		cin >> x;
	}

	string s = to_string(x);

	return 0;
}