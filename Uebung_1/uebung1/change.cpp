
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

void change(const int due, const int paid, std::ostream& out)
{
	// ToDo: compute and print set of change tuples
	int change = paid - due;
	int w[] = {5000,2000,1000,500,200,100,50,20,10,5,2,1} ;
	out << "coin,num" << std::endl;


	for(int i = 0; i<12; i++){
		if (change>=w[i]){
			out << w[i] << "," << change/w[i] << std::endl;
			change = change - ((change/w[i]) * w[i]);
		}
	}


}

int main(int argc, char * argv[]){
	if(argc != 3 && argc != 5)
		return 1;	// invalid number of parameters

	int due = std::stoi(argv[1]);
	int paid = std::stoi(argv[2]);
	std::ostream* os = NULL;
	std::ofstream file;


	if(due > paid){
		std::cerr << "Pay more" << std::endl;
		return 1;
	}

	if(argc == 3){
		os = &std::cout;

	}

	if(argc == 5){
		if (strcmp(argv[3], "-o")){		//strcmp 0 if same
			std::cerr << "Parameter "<< argv[3] << " is invalid" << std::endl;
			return 1;
		}
		std::string filename = argv[4];
		file.open(filename + ".txt",std::ios::out); //Annahme Textdatei meinte .txt Datei
	 	os = &file;
	}

	// ToDo: catch invalid arguments

	change(due, paid, *os);

	if (argc == 5) {
		file.close();
	}
	return 0;
}
