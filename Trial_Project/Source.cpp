#include <iostream>
#include <string>

using namespace std;


// example of inheritance between classes
class A
{
public:
	virtual int value() { return 1; }
};

class B : public A
{
public:
	int value() { return 2; }
};





// example of destructor
class MyClass
{
public :
	~MyClass();
	
};

// destructor
MyClass::~MyClass()
= default;




// 
typedef struct
{
	char a;
	int b;
} myStruct;






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

	// create new pointer of MyClass
	auto* p = new MyClass();
	// delete pointer using destructor
	delete p;

	
	A* obj = new B();
	int val = obj->value();

	cout << "Val = " << val << endl;


	// use of typedef struct above
	myStruct s1;
	s1.a = 'a';
	s1.b = 3;

	myStruct s2;
	s2 = s1;

	cout << "Struct s2: " << s2.b;


	// pointers
	// r is the pointer
	// a is the variable
	// &a is the reference for a
	int a = 5;
	int *r = &a;

	cout << "r: " << r;
	

	return 0;
}
