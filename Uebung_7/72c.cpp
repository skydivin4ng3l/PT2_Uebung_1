#include <iostream>
#include <vector>

using namespace std;

void selectionSort(vector<int>& A) {
	const int N = A.size();
	for (int j = N; j >= 0; --j) {
		//search maximum in the range [0,j] //This is NOT correct
		int m = j; // this must be -1 
		for (int i = 0; i < j; i++) {
			if (A[i] < A[m]) m = i; //a[7] out of range!! Sec fault, smaller than 20 will 
		}
		//swap the maximal element to the j-th position // THIS IS NOT CORRECT
		swap(A[j], A[m]); //absteigend sortiert
	}
}

int main(int argc, char** argv){
	vector<int> test = { 10,20,1,7,13,6,18 };

	for (auto &t : test)
	{
		cout << t << " ";
	}
	
	cout << endl;

	selectionSort(test);

	for (auto &t : test)
	{
		cout << t << " ";
	}

	return 0;
}
