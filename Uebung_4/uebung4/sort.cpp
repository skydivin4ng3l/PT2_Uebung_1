#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cassert>

// function template for printing contents of containers to std::cout
template<class T>
void printContainer(T& container)
{
	std::cout << "{";
	for (auto element : container)
		std::cout << element << " ";
	std::cout << "}" << std::endl;
}

// Todo 4.4 - Merge the given lists [leftIt..midIt) and [midIt..rightIt)
template<class T>
void merge(T leftIt, T midIt, T rightIt)
{
	assert(leftIt <= midIt && midIt <= rightIt);

	std::vector<typename T::value_type> mergedValues(rightIt - leftIt);

	auto writeIt = leftIt;
	auto constMidIt = midIt;

	//take smallest and put it into the merged container
	for(int i = 0; i<mergedValues.size(); i++){
		if(midIt == rightIt)							//right part already empty
			mergedValues[i] = *(leftIt++);
		else if(leftIt == constMidIt)			//leftpart already empty
			mergedValues[i] = *(midIt++);
		else if(*leftIt <= *midIt)				//if in both parts elements left and left one is smaller or equal
			mergedValues[i] = *(leftIt++);
		else if(*midIt < *leftIt)					//if in both parts elements left and right one is smaller
			mergedValues[i] = *(midIt++);
	}

	for(int i=0; i<mergedValues.size(); i++)
		*(writeIt++) = mergedValues[i];

}


// Todo 4.4 - Sort the given container using merge sort.
template<class T>
void mergeSort(T leftIt, T rightIt)
{
	assert(leftIt < rightIt);

	if(std::distance(leftIt,rightIt)!=1){
		auto midIt = leftIt + (std::distance(leftIt,rightIt)+1)/2;

		mergeSort(leftIt,midIt);
		mergeSort(midIt,rightIt);
		merge(leftIt,midIt,rightIt);
	}

}

int main(int argc, char** argv)
{
	// define sample data
	std::vector<int> sampleDataInt = { 10, 1, 12, 33, 24, 5, 6, -7, -2, 19 };
	std::vector<std::string> sampleDataString = { "Die", "eines", "ist", "Gebrauch", "der", "Sprache", "in", "sein", "Wortes", "Bedeutung" };

	// test for integer vector
	printContainer(sampleDataInt);
	mergeSort(sampleDataInt.begin(), sampleDataInt.end());
	printContainer(sampleDataInt);

	// test for string vector
	printContainer(sampleDataString);
	mergeSort(sampleDataString.begin(), sampleDataString.end());
	printContainer(sampleDataString);

	return 0;
}
