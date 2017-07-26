#include <iostream>
#include <string>

using namespace std;

class Test {
public:
	const string getLabel() const {
		return label_;
	}

private:
	Test() {};
	Test(string label) : label_(label) {};
	~Test() {};
	string label_;
};

int main(int argc, char** argv) {
	Test* t1 = new Test("Test1"); //we use new to get a pointer to the new object back
	Test t2("Test2");

	cout << t1.getLabel() << endl;
	cout << t2->getLabel() << endl; //we use -> to access members of object pointers same as (*obj_ptr).member


}