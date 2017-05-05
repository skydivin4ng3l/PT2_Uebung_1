
#include <cstdlib>
#include <iostream>

long count=0;

int fibonacci(int number)
{
	// ToDo: Exercise 2.c - count number of calculation steps
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

}

int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	int n = std::atoi(argv[1]);

	// ToDo: Exercise 2.c - print calculation steps

    std::cout << n << " : " <<fibonacci(n) << " : #"<< count << std::endl;

	return 0;
}
