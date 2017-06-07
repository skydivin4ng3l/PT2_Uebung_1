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
	//prepare iterators for front and middle section
	auto container_old_size = container.size();
	container.reserve(container_old_size * 3);
	auto end_old_it = container.end();

	auto begin_middle_it = container.begin();
	begin_middle_it = std::next(begin_middle_it, container_old_size);
	container.resize(container_old_size*2);
	auto end_middle_it = container.end();

	//copy and prep for adjacent diff
	std::copy_backward(container.begin(), container.end()-container_old_size, container.end());
	container.push_back(*container.begin());

	//transform midsection to adjacent diff 
	std::adjacent_difference(container.begin() + container_old_size, container.end(), container.begin() + container_old_size);
	container.erase(container.begin()+container_old_size);

	//increase container size to full and generate ooposite diffs and move everything in place
	container.resize(container.size() + container_old_size);

	// thos iterators seam not to work as intended,...totally unclear
	auto rev_dif_it = std::next(std::rbegin(container), container_old_size - 1);
	auto rev_old_it = container.rbegin() + (container_old_size*2 - 1);
	auto rev_new_it = container.rbegin();

	printContainer(container);
	
	std::cout << "rev_dif_it " << *rev_dif_it << std::endl;
	std::cout << "rev_old_it " << *rev_old_it << std::endl;
	std::cout << "rev_new_it " << *rev_new_it << std::endl;
	//fix circular end
	*(rev_new_it++) = *(rev_dif_it++);

	while (rev_new_it != std::next(container.rend(),1) )
	{
		/**(rev_new_it++) = *(rev_old_it++);
		*(rev_new_it++) = (*rev_dif_it) * (-1);
		*(rev_new_it++) = *(rev_dif_it++);*/
	}

	//fix circular begin
	/**container.begin() = (*container.end()) * (-1);*/


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
