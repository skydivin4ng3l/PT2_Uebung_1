#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cfloat>
#include <iomanip>
#include <vector>
#include <ctime>

// transforms a string to a date. Throws a logic_error if year is *not* between 2005 and 2015
std::tm stringToTime(std::string date)
{
	std::tm t;
#if defined(__GNUC__) && (__GNUC__ < 5)
	strptime(date.c_str(), "%d.%m.%Y", &t);
#else
	std::istringstream ss(date);
	ss >> std::get_time(&t, "%d.%m.%Y");
#endif

	if(t.tm_year < 105 || t.tm_year > 115)
		throw std::logic_error("Year should be between 2005 and 2015");

	return t;
}

struct FormatException
{
	int m_actLine;
	std::string m_actFields;

	FormatException()
	{
		m_actLine = 0;
		m_actFields = "";
	}
};

void parseLine(std::string line, int lineNum)
{
	const std::string fieldNames[3] = { "Date", "Temperature", "Rainfall" };

	// TODO 3.1b: parse a given line, check dates by calling stringToTime, check temperature/rainfall by calling std::stof.
	//skip firstline
	
	std::istringstream linestream;
	linestream.str(line);
	FormatException parseLineException;

	for (std::string fieldName : fieldNames)
	{
		std::string parsedField;
		std::getline(linestream, parsedField, ';');
		
		try
		{
			if (fieldName=="Date")
			{
				stringToTime(parsedField);
			}
			else
			{
				std::stof(parsedField);
			}
		}
		// Catch all exceptions thrown by these methods.
		// If there have been any exceptions, aggregate all necessary information into an instance of FormatException and throw that instance.
		catch (...)
		{
			if (parseLineException.m_actLine == lineNum)
			{
				parseLineException.m_actFields += " " + fieldName;
			} 
			else
			{
				parseLineException.m_actLine = lineNum;
				parseLineException.m_actFields = fieldName;
			}
		}

	}

	if (parseLineException.m_actLine)
	{
		throw parseLineException;
	}
	
}

// TODO 3.1d
void writeOutFormatException(const FormatException& e)
{
	std::ofstream logfile;
	static bool logfilecleared = false;
	logfile.exceptions(std::ios_base::badbit | std::ios_base::failbit);

	try
	{
		if (!logfilecleared)
		{
			logfile.open("exceptions.log", std::ofstream::trunc);
			logfilecleared = true;
		}
		else
		{
			logfile.open("exceptions.log", std::ofstream::app);
		}

		logfile << "Failure on line " << e.m_actLine << ", field(s): " << e.m_actFields << std::endl;
		logfile.close();
	}
	catch (const std::ios_base::failure& e)
	{
		std::cerr << "Read/Write Error: " << e.what() << std::endl;
	}

}

bool myGetLine(std::ifstream& file, std::string& line)
{
	try
	{
		if (std::getline(file, line)) //returns true as long as there is no exception(including EOF)
		{ 
			return true; 
		}
		else // for safety reasons should never fire cause EOF is handled as exception
		{
			return false;
		}
	}
	catch (const std::ios_base::failure&)
	{
		if (file.eof() == false) { throw; } //pushes the throw, unless EOF is found
		return false; //EOF is found
	}
}

void checkData(std::string path)
{
	int validLines = 0;
	int invalidLines = 0;
	std::ifstream file;
	file.exceptions(std::ios_base::badbit | std::ios_base::failbit);
	// TODO 3.1a: open file + read each line + call parseLine function (catch ifstream::failure)
	// TODO 3.1c: read each line + call parseLine function (catch FormatException) + count valid + invalid lines
	try
	{
		file.open(path);
		std::string line;
		int lineNum = 0;

		while (myGetLine(file, line)) 
		{
			lineNum++;
			
			//ignore Header no Data
			if (lineNum == 1) continue;

			try
			{
				parseLine(line, lineNum);
				validLines++;
			}
			catch (const FormatException& parseLineException)
			{
				invalidLines++;
				writeOutFormatException(parseLineException);
			}
		}

		file.close();

	}
	catch (const std::ios_base::failure& e)
	{
		std::cerr << "Read/Write Error: " << e.what() << std::endl;
	}

	std::cout << "valid data fields: " << validLines << " - invalid data fields: " << invalidLines << std::endl;
}

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		std::cout << "Invalid number of arguments - USAGE: exceptions [DATASET]" << std::endl;
		return -1;
	}

	checkData(argv[1]);

	return 0;
}
