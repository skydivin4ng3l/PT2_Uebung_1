#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>

#define MY_DELIMITER ';'
#define COLUMNS_TO_CHECK {5, 8, 10}

bool isValueCorrect(const std::string &teststring, const int &column)
{
	std::regex regExp;

	switch (column)
	{
		// example regExp for column 1
		/*case 1:
			regExp = "[a-zA-Z]+";
			break;*/

		// Todo: implement cases for other columns
		case 5:
			regExp = "(^$|^[A-Z0-9]{3,4}$"
		default:
			regExp = ".*";
			break;
	}

	return std::regex_match(teststring, regExp);
}

void readTokensAndLines(char* path)
{
	std::ifstream file(path);
	std::string parsed, line;

	while (std::getline(file, line)) {
		std::istringstream linestream;
		linestream.str(line);

		std::vector<std::string> linevector;

		// Todo: - Split line and write result to std::cout
		while (std::getline(linestream, parsed, MY_DELIMITER))
		{
			linevector.push_back(parsed);
		}

		try
		{
			//access 5. element ICAO, 8. element Altitude, 10. element DST
			std::vector<int> columnstocheck = COLUMNS_TO_CHECK;
			for (int column : columnstocheck ) //correct?
			{
				if (isValueCorrect(linevector.at(column), column) == false) 
				{
					//Log to file
				}
			}
			std::cout << linevector.at(1) << " - " << linevector.at(11) << std::endl;
		}
		catch (const std::out_of_range& e)
		{
			std::cout << std::endl << "Error: linevector out of range: Following line has not enough Values" << std::endl;
			std::cout << line << std::endl << std::endl;
		}
		

		//       - Check each part of line with isValueCorrect and log if values are not supported
		//       - Use and extend isValueCorrect function for this


	}
}

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		std::cout << "not enough arguments - USAGE: fileio [DATASET]" << std::endl;
		return -1; // invalid number of parameters
	}

	std::cout << "Given path to airports.dat: " << argv[1] << std::endl;

	readTokensAndLines(argv[1]);

	return 0;
}
