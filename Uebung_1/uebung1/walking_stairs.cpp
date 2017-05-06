
#include <cstdlib>
#include <iostream>


// ToDo: Exercise 2.d - adapt and implement combinations

unsigned long long fibonacci(int number){

	unsigned long long current = 0;
	unsigned long long previous = 0;
	unsigned long long pre_previous = 1;

	for (int i = 0; i < number; i++) {
		current = previous + pre_previous;
		pre_previous = previous;
		previous = current;
	}

	return current;

}

unsigned long long combinations(int number)
{
	return fibonacci(number+1);
}


int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	int n = std::atoi(argv[1]);

	std::cout << combinations(n) << std::endl;

	return 0;
}
