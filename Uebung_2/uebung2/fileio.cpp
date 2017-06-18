#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>

//#define MY_DELIMITER ';'
#define MY_DELIMITER ','

#define AIRPORT_NAME 1
#define ICAO 5
#define ALTITUDE 8
#define DST 10
#define DATABASE_TIME_ZONE 11

#define COLUMNS_TO_CHECK {ICAO, ALTITUDE, DST}

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
		regExp = "((^$)|(^[A-Z0-9]{3,4}$))";
		break;
	case 8:
		regExp = "((^[12]{1}[0-9]{4}$)|(^[1-9]{1}[0-9]{1,3}$)|(^[0-9]{1}$))"; // (10.000 -29.999)|(10-9.999)|(0-9)
		break;
	case 10:
		regExp = "^([EASOZNU]{1})$";
		break;
	default:
		regExp = ".*";
		break;
	}

	return std::regex_match(teststring, regExp);
}

std::string cleanUpString(std::string& parsed)
{
	if (!parsed.empty())
	{
		if (parsed.front() == ('"') && parsed.back() == '"')
		{
			parsed.erase(parsed.begin());
			parsed.erase(parsed.end() - 1);
		}		
	}
	return parsed;
}

void logLineErrors(const std::string line, std::ostringstream& logstream, const std::vector<std::string>& linevector)
{
	std::vector<int> columnstocheck = COLUMNS_TO_CHECK;
	for (int column : columnstocheck)
	{
		if (isValueCorrect(linevector.at(column), column) == false)
		{
			logstream << line << " Error at Column: " << column << " cause \"" << linevector.at(column) << "\" is not valid"<< std::endl;
		}
	}
}

void printLogToFile(std::ostringstream &logstream)
{
	std::ofstream logfile;

	if (!logfile.is_open())
	{
		logfile.open("fileio.log", std::ofstream::trunc);
		logfile << logstream.str();
		logfile.close();
	}
}

bool ignoreDelimiter(std::string &parsed, bool ignoredelimiter, std::string &incompletestring)
{
	if (!parsed.empty())
	{
		if (ignoredelimiter == false && parsed.front() == '"' && parsed.back() != '"')
		{
			parsed.push_back(MY_DELIMITER);
			incompletestring = parsed;
			return true;
		}
		else if (ignoredelimiter == true)
		{
			if (parsed.back() == '"')
			{
				incompletestring += parsed;
				parsed = incompletestring;
				incompletestring.clear();
				return false;
			}
			else
			{
				parsed.push_back(MY_DELIMITER);
				incompletestring += parsed;
				return true;
			}
		}
	}
	return false;
}

void readTokensAndLines(char* path)
{
	try
	{
		std::ifstream file(path);
		std::string parsed, line;

		std::ostringstream logstream;
	
		while (std::getline(file, line))
		{
			std::istringstream linestream;
			linestream.str(line); //overwrite the stream with the contents of "string" line
			//Split line and write result to std::cout	
			try
			{
				std::vector<std::string> linevector;
				bool ignoredelimiter = false;
				std::string incompletestring = "";
				while (std::getline(linestream, parsed, MY_DELIMITER))
				{
					ignoredelimiter = ignoreDelimiter(parsed, ignoredelimiter, incompletestring);
				
					if (ignoredelimiter == false)
					{	
						parsed = cleanUpString(parsed);
						linevector.push_back(parsed);
					} 				
				}
				std::cout << linevector.at(AIRPORT_NAME) << " - " << linevector.at(DATABASE_TIME_ZONE) << std::endl;
				//Check each part of line with isValueCorrect and log if values are not supported
				logLineErrors(line, logstream, linevector);				
			}
			catch (const std::out_of_range&)
			{
				std::cout << std::endl << "Error: linevector out of range: Following line has not enough Values" << std::endl;
				std::cout << line << std::endl << std::endl;
			}
		}
		printLogToFile(logstream);
	}
	catch (const std::ios_base::failure&)
	{
		std::cerr << "File Read/Write error" << std::endl;
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
