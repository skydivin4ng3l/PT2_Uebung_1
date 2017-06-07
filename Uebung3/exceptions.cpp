#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cfloat>
#include <iomanip>
#include <vector>
#include <ctime>

#define LOGPATH "weather.log"
// transforms a string to a date. Throws a logic_error if year is *not* between 2005 and 2015
std::tm stringToTime(std::string date){
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

struct FormatException{
	int m_actLine;
	std::string m_actFields;
};

void parseLine(std::string line, int lineNum){
	const std::string fieldNames[3] = { "Date", "Temperature", "Rainfall" };

	// TODO 3.1b: parse a given line, check dates by calling stringToTime, check temperature/rainfall by calling std::stof.
	// Catch all exceptions thrown by these methods.
	// If there have been any exceptions, aggregate all necessary information into an instance of FormatException and throw that instance.

	//necessary items for parsing
	std::istringstream linestream;
	linestream.str(line);
	std::string parsed;

	std::vector<std::string> data;
	data.clear();

	bool invalid=false;
	FormatException e;
	e.m_actLine = lineNum;


	while (std::getline(linestream, parsed, ';')){
			data.push_back(parsed);
	}

	try{
		stringToTime(data[0]);
	}catch(std::exception){
		e.m_actFields.append(fieldNames[0]+" ");
		invalid = true;
	}

	try{
		std::stof(data[1]);
	}catch(...){
		e.m_actFields.append(fieldNames[1]+" ");
		invalid = true;
	}

	try{
		std::stof(data[2]);
	}catch(...){
		e.m_actFields.append(fieldNames[2]);
		invalid = true;
	}

	if(invalid)
		throw e;

	return;
}

// TODO 3.1d
void writeOutFormatException(const FormatException& e){
	//Opening logfile (create if not existing)
	std::ofstream logfile;
	logfile.open(LOGPATH, std::ios_base::app | std::ios_base::out);

	if(logfile.fail()){
		std::cerr << "Fehler beim öffnen der Datei." << std::endl;
		//More helpful Error Message than e.what()
		std::cerr << strerror(errno) << std::endl;
	}

	logfile.exceptions(logfile.exceptions() | logfile.failbit | logfile.badbit);


	try{
		//Writing logfile
		logfile << "Failure on line " << e.m_actLine << ", ";
		logfile << "field(s): " << e.m_actFields << std::endl;

		logfile.close();
	}catch(std::ios_base::failure &exc){
		std::cerr	<< "Error Message: " << exc.what() << std::endl;
		std::cerr << strerror(errno) << std::endl;
	}

	return;
}

void checkData(std::string path){
	int validLines = 0;
	int invalidLines = 0;
	std::ifstream file;

	// TODO 3.1a: open file + read each line + call parseLine function (catch ifstream::failure)

	//try to open file with given path
	try{
		file.open(path);
		//Prepare Exceptionmask of file
		file.exceptions(file.exceptions() | file.failbit | file.badbit);
	}catch (std::ios_base::failure &e){
		std::cerr << "Fehler beim öffnen der Datei." << std::endl;
		std::cerr	<< "Error Message: " << e.what() << std::endl;
		//More helpful Error Message than e.what()
		std::cerr << strerror(errno) << std::endl;

		// try{
		// 	file.close();
		// }catch(std::ios_base::failure &e){
		// 	std::cerr << "Error Message: " << e.what() << std::endl;
		// }

		return;
	}

	// TODO 3.1c: read each line + call parseLine function (catch FormatException) + count valid + invalid lines
	//read
	std::string line;
	int lineNum=0;
	try{
		while(std::getline(file,line)){
			lineNum++;

			//Ignore first line, only header no data
			if(lineNum == 1)
				continue;

			try{
				parseLine(line,lineNum);
				validLines++;
			}catch(FormatException &e){
				writeOutFormatException(e);
				invalidLines++;
			}
		}
	}catch(std::ios_base::failure &e){
		if(!file.eof()){
			std::cerr << "Fehler beim lesen der Datei." << std::endl;
			std::cerr << "Error Message: " << e.what();
			//More helpful Error Message than e.what()
			std::cerr << strerror(errno) << std::endl;

			return;
		}
	}


	std::cout << "valid data fields: " << validLines << " - invalid data fields: " << invalidLines << std::endl;
}

int main(int argc, char * argv[]){
	if(argc != 2)
	{
		std::cout << "Invalid number of arguments - USAGE: exceptions [DATASET]" << std::endl;
		return -1;
	}

	//Remove if old logfile exists
	std::ifstream logfile(LOGPATH);
	if(logfile.good())
		std::remove(LOGPATH);


	checkData(argv[1]);

	return 0;
}
