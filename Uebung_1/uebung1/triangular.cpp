
#include <cstdlib>
#include <iostream>
#include <climits>

#include <cmath>
#include <string>



int triangular(int number){
	// ToDo: Exercise 1.a - return triangular number
	int trisum = 0;
	for (int i = 0; i <= number; i++) {
			trisum += i;
	}
	return trisum;
	//return ( number * (number +1) ) / 2;
}

void pretty_print(int decimal)
{
	
	//decimal = triangular(decimal);
	// ToDo: Exercise 1.c - print number with decimal marks to console
	std::string decimal_string = std::to_string(decimal);
	
	size_t string_length = decimal_string.length();
	
	if (string_length > 3 ) {
		for ( size_t i = 3 ; i < string_length ; i += 3 ) {
			decimal_string.insert( string_length - i , ".");  // additional character should not interfier with the calculated position of the next "."
		}
	}
	std::cout << decimal_string << std::endl;
}

int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	int n = std::atoi(argv[1]);

	// ToDo: Exercise 1.c - print all numbers with decimal marks

	// ToDo: Exercise 1.b - check if n is in domain, if not print valid domain and codomain and return 2
	
	//Gaußsche Summenformel und quadratische Ergänzung
	long max_n = (long) floor( sqrt( ( 2.0 * INT_MAX ) + (1.0/4.0) ) - (1.0/2.0) ) ;
    long max_tri = triangular( max_n );

	
	if ( n <= max_n && n >= 1 ) {
		pretty_print( triangular( n ) );
		std::cout << std::numeric_limits<unsigned long>::max() << std::endl;
		std::cout << std::numeric_limits<unsigned long long>::max();
	} else {
		std::cout << "domain = [<1>;<" << max_n << ">] , codomain = [<1>;<" << max_tri << ">]\n";
	// ToDo: Exercise 1.a - print triangular number to console
	//std::cout << "max_n " << max_n << " and max_tri  " << max_tri <<"\n";
	
		
	}
	
	return 0;
}
