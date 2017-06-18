
#include <cstdlib>
#include <iostream>


// ToDo: Exercise 2.d - adapt and implement combinations
unsigned long long fibonacci( int number )
{
	if ( number > 1 && number <= 93 ) { // 94 would cause overflow (entered 93 by argument)
		unsigned long long current = 1ull;
		unsigned long long previous = 1ull;
		unsigned long long pre_previous = 0ull;

		for ( int i = 2 ; i <= number ; i++ ) {
			current = previous + pre_previous;
			pre_previous = previous;
			previous = current;
		}

		return current;
	}
	else return 0;
}


unsigned long long combinations( int number )
{
	return fibonacci( number + 1 );
}


int main( int argc , char * argv[] )
{
	if( argc != 2 )
		return 1;	// invalid number of parameters

	int n = std::atoi( argv[1] );

	std::cout << combinations( n );

	return 0;
}
