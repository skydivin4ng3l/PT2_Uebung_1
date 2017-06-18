
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void change(const int due, const int paid, std::ostream& out)
{
	// ToDo: compute and print set of change tuples
	// calculate return value
	int change_return = paid - due;
	
	//List of change return Values
	const std::vector <int> change_coins = { 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5, 2, 1 };

	//print table header
	out << "coin,num" << std::endl ;

	//Calculation of need sum of change_coins
	for (auto current_coin : change_coins)
	{
		//is there still money to return?
		if (change_return)
		{
			//calc if the current_coin can be returned and how much of it
			int count_current_coin = change_return / current_coin;
			//if current_coin can be retruned 
			if (count_current_coin)
			{
				out << current_coin << "," << count_current_coin << std::endl;
				//calculation of rest
				change_return -= current_coin * count_current_coin;
			}
			else //current_coin can not be returned
			{
				continue;
			}
			
		}
		else //no more money can be returned
		{
			break;
		}
	}
}

int main(int argc, char * argv[])
{
	if(argc != 3 && argc != 5)
		return 1;	// invalid number of parameters

	int due = std::stoi(argv[1]);
	int paid = std::stoi(argv[2]);
	std::ostream* os = NULL;
	std::ofstream file;


	if (due > paid) {
		std::cerr << "Pay more" << std::endl;
		return 1;
	}

	if (argc == 3) {
		os = &std::cout;

	}

	if (argc == 5) {
		if (strcmp(argv[3], "-o")) {		//strcmp 0 if same
			std::cerr << "Parameter " << argv[3] << " is invalid" << std::endl;
			return 1;
		}
		std::string filename = argv[4];
		file.open(filename + ".txt", std::ios::out); //Annahme Textdatei meinte .txt Datei
		os = &file;
	}

	// ToDo: catch invalid arguments

	change(due, paid, *os);

	if (argc == 5) {
		file.close();
	}
	return 0;
}
