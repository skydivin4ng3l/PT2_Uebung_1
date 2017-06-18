
#include <cstdlib>
#include <iostream>

<<<<<<< HEAD
int number_of_summations = 0;
=======
long count=0;
>>>>>>> 905dc41ff5e7421cfc419aa2fcd775ea2f2a71fc

int fibonacci(int number)
{
	// ToDo: Exercise 2.c - count number of calculation steps
<<<<<<< HEAD
	number_of_summations++;
	// ToDo: Exercise 2.a - return 0 on bad arguments
	if( number < 1 || number > 46 ) {
		return 0;
	}
	// ToDo: Exercise 2.a - retrieve nth fibonacci number recursively
	if (number <= 2) {
		return 1;
	}
	else {
		return fibonacci( number - 1 ) + fibonacci( number - 2 );
	}
=======
    count++;

	// ToDo: Exercise 2.a - return 0 on bad arguments
    if (number<=0 || number > 46){
    return 0;
    }
	// ToDo: Exercise 2.a - retrieve nth fibonacci number recursively
    if (number <= 2){
        return 1;
    }
    else{
        return fibonacci(number-1)+fibonacci(number-2);
    }
>>>>>>> 905dc41ff5e7421cfc419aa2fcd775ea2f2a71fc

}

int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	int n = std::atoi(argv[1]);

	// ToDo: Exercise 2.c - print calculation steps

<<<<<<< HEAD
	std::cout << n << " : " << fibonacci(n) << " : #" << number_of_summations << "\n";
=======
    std::cout << n << " : " <<fibonacci(n) << " : #"<< count << std::endl;
>>>>>>> 905dc41ff5e7421cfc419aa2fcd775ea2f2a71fc

	return 0;
}
