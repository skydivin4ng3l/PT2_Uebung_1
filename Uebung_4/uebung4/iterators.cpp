#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <iterator>

#include <numeric>
#include <functional>

// function template for printing contents of containers to std::cout
template<class T>
void printContainer(T& container)
{
	std::cout << "{";
	for(auto element : container)
		std::cout << element << " ";
	std::cout << "}" << std::endl;
}


// Todo 4.2a - Merge front-back pairings of elements of inContainer into outContainer. Do *not* use the []-operator.
template<class T>
void front_back_pairing(T& inContainer, T& outContainer)
{
	outContainer.resize(inContainer.size());

	auto currentInF_It = inContainer.begin();
	auto currentInR_It = inContainer.rbegin();

	for (auto currentOut_It = outContainer.begin(); currentOut_It != outContainer.end(); )
	{
		*(currentOut_It++) = *(currentInF_It++);
		if (currentOut_It != outContainer.end())
		{
			*(currentOut_It++) = *(currentInR_It++);
		}
	}

}

// Todo 4.2b - Remove all duplicates from the given container. Do *not* use the []-operator.
template<class T>
void remove_duplicates(T& container)
{
	std::sort(container.begin(), container.end());
	container.erase(std::unique(container.begin(), container.end()),
					container.end());
}

// Todo 4.2c - Expand the given container by inserting the numerical differences of each element to its neighbors. Do *not* use the []-operator.
template<class T>
void insert_differences(T& container)
{
	//prepare support variables and container
	auto container_old_size = container.size();

	T dif_container;
	dif_container.resize(container_old_size);

	//copy and prep for adjacent diff
	std::copy(container.begin(), container.end(), dif_container.begin());
	dif_container.push_back(*container.begin()); //add first element to end for circular diff behavior
	
	//transform support container to adjacent diff / lookup container 
	std::adjacent_difference(dif_container.begin(), dif_container.end(), dif_container.begin());
	dif_container.erase(dif_container.begin()); //remove by adjacent diff unchanged element

	container.resize(container_old_size*3);

	// traversal iterators
	auto rev_dif_it = dif_container.rbegin();
	auto rev_old_it = container.rbegin() + (container_old_size*2);
	auto rev_new_it = container.rbegin();

	//fix circular end
	*(rev_new_it++) = *(rev_dif_it++);

	while (rev_new_it + 2 != container.rend())
	{
		*(rev_new_it++) = *(rev_old_it++);
		*(rev_new_it++) = -(*rev_dif_it);
		*(rev_new_it++) = *(rev_dif_it++);
	}

	//fix circular begin
	*rev_new_it = *rev_old_it;
	*container.begin() = -*( container.begin()+(container.size()-1) );


	//-----------------can not adanve iterator vector + offset error?!?!??!
	/*auto temp = *(container.end() - 1) - *container.begin();

	auto emplace_it = container.begin();
	container.emplace(emplace_it, temp);
	std::next(emplace_it, 2);
	*emplace_it = 99;
	auto input_it = container.begin()+1;
	temp = *(emplace_it++) - *(input_it++);
	container.emplace(emplace_it, temp);

	while (input_it != container.end())
	{
		temp = *(emplace_it++) - *(input_it);
		container.emplace(emplace_it, temp);
		temp = *(input_it++) - *emplace_it;
		container.emplace(emplace_it, temp);
		input_it + 2;
		emplace_it + 2;
	}

	temp = *(container.begin() + 1) - *container.end();
	container.push_back(temp);*/
	//----------------------------------------------------------------------

	//container.reserve(container.size() * 3);
	//auto input_rev_old_it = container.rbegin();

	//container.resize(container.size() * 3);
	//auto output_rev_new_it = container.rbegin();

	//Special case end value difference  begin-end
	//*(output_rev_new_it++) = *container.begin() - *input_rev_old_it;
	//*(output_rev_new_it++) = *input_rev_old_it;

	//while (input_rev_old_it != container.rend()-1)
	//{
	//	if (input_rev_old_it == container.rend() - 1) break;
	//	*(output_rev_new_it++) = *(--input_rev_old_it) - *(++input_rev_old_it++);
	//	/*if (input_rev_old_it == container.rend() - 1) break;
	//	*(output_rev_new_it++) = *input_rev_old_it;*/
	//}

	//Special case end value difference  end-begin
	//*output_rev_new_it = *(container.end()-1) - *input_rev_old_it;
	
}

void testFrontBackPairingFunctionality()
{
	// define sample data
	std::vector<int> sampleDataInt = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	std::list<std::string> sampleDataString = { "Die", "eines", "ist", "Gebrauch", "der", "Sprache", "in", "sein", "Wortes", "Bedeutung" };

	// test for integer vector
	std::vector<int> helpIntVector;
	front_back_pairing(sampleDataInt, helpIntVector);
	printContainer(sampleDataInt);
	printContainer(helpIntVector);

	// test for string list
	std::list<std::string> helpStringList;
	front_back_pairing(sampleDataString, helpStringList);
	printContainer(sampleDataString);
	printContainer(helpStringList);
}

void testRemoveDuplicateFunctionality()
{
	// define sample data
	std::vector<int> sampleDataInt = { 10, 11, 10, 13, 14, 15, 15, 15, 18, 19, 12, 11, 17 };
	std::vector<std::string> sampleDataString = { "Die", "___", "eines", "ist", "Gebrauch", "der", "Sprache", "in", "sein", "Wortes", "Bedeutung", "Die", "ist", "blabla" };

	// test for integer vector
	printContainer(sampleDataInt);
	remove_duplicates(sampleDataInt);
	printContainer(sampleDataInt);

	// test for string vector
	printContainer(sampleDataString);
	remove_duplicates(sampleDataString);
	printContainer(sampleDataString);
}

void testAddDifferenceFunctionality()
{
	// define sample data
	std::vector<int> sampleDataInt = { 10, 11, 14, 16, 1, 18 };

	// test for integer vector
	printContainer(sampleDataInt);
	insert_differences(sampleDataInt);
	printContainer(sampleDataInt);
}

int main(int argc, char** argv)
{
	testFrontBackPairingFunctionality();
	testRemoveDuplicateFunctionality();
	testAddDifferenceFunctionality();

	return 0;
}
