#include <iostream>
#include <list>

using namespace std;

int main()
{
	int myints[] = { 17,89,7,14,89 };
	list<int> mylist(myints, myints + 5);

	mylist.remove(8);
	mylist.remove(7);

	for (auto it = mylist.begin(); it != mylist.end(); ++it)
		cout << ' ' << *it;

	return 0;
}