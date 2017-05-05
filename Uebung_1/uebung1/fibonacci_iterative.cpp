
#include <cstdlib>
#include <iostream>

int number_of_summations = 0;

int fibonacci(int number)
{
	// ToDo: Exercise 2.c - count number of calculation steps
	
	// ToDo: Exercise 2.b - return 0 on bad arguments
	if( number > 1 && number <= 46 ) {
		// ToDo: Exercise 2.b - retrieve nth fibonacci number iteratively
		int current = 1;
		int previous = 1;
		int pre_previous = 0;
		for( int i = 2 ; i <= number ; i++) {
			current = previous + pre_previous;
			pre_previous = previous;
			previous = current;
			number_of_summations++;
		}

		return current;
	} else return 0;
}

int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	int n = std::atoi(argv[1]);

	// ToDo: Exercise 2.c - print calculation steps

	std::cout << n << " : " << fibonacci(n) << " : #" << number_of_summations << "\n";

	return 0;
}
