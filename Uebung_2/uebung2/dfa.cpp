#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::string step(std::string state, int value)
{
	// Todo: Handle all possible states and values and return the respective new state
	// Note: Accepted coin values are {10, 20, 50}.
	bool invalid = false;

	if (!state.compare("0")){
		switch (value) {
			case 10: state = "10";break;
			case 20: state = "20";break;
			case 50: state = "dispense";break;
			default: invalid = true;
		}
	}else if(!state.compare("10")){
		switch (value) {
			case 10: state = "20";break;
			case 20: state = "30";break;
			case 50: state = "dispense";break;
			default: invalid = true;
		}
	}else if(!state.compare("20")){
		switch (value) {
			case 10: state = "30";break;
			case 20: state = "40";break;
			case 50: state = "dispense";break;
			default: invalid = true;
		}
	}else if(!state.compare("30")){
		switch (value) {
			case 10: state = "40";break;
			case 20: ;
			case 50: state = "dispense";break;
			default: invalid = true;
		}
	}else if(!state.compare("40")){
		switch (value) {
			case 10: ;
			case 20: ;
			case 50: state = "dispense";break;
			default: invalid = true;
		}
	}


	// for all states and inputs which are not handled above show a message and return original state
	if (invalid)
		std::cout << "Invalid input.\n";

	return state;
}


std::string stepExtended(std::string state, int value)
{
	// Todo: Handle all possible states and values and return the respective new state
	// Note: Accepted coin values are {10, 20, 50}. Accepted drink selection values are {1, 2, 3}.
	bool invalid = false;

	if (!state.compare("0")){
		if (value<4 && value>0){
			state = std::to_string(value);
			return state;
		}else
			invalid = true;
	}

	if (!state.compare("1") || !state.compare("2") || !state.compare("3")){

		if (!state.compare("1") && value==50)
			state = "dispense";
		else if (value == 10 || value == 20 || value == 50)
			state.append(std::to_string(value));
		else
			std::cout << "Invalid input.\n";

		return state;
	}

	if(state[0]=='1'){
		if(!state.substr(1).compare("10")){
			switch (value) {
				case 10: state.replace(1,2,"20");break;
				case 20: state.replace(1,2,"30");break;
				case 50: state = "dispense";break;
				default: invalid = true;
			}
		}else if(!state.substr(1).compare("20")){
			switch (value) {
				case 10: state.replace(1,2,"30");break;
				case 20: state.replace(1,2,"40");break;
				case 50: state = "dispense";break;
				default: invalid = true;
			}
		}else if(!state.substr(1).compare("30")){
			switch (value) {
				case 10: state.replace(1,2,"40");break;
				case 20: ;
				case 50: state = "dispense";break;
				default: invalid = true;
			}
		}else if(!state.substr(1).compare("40")){
			switch (value) {
				case 10: ;
				case 20: ;
				case 50: state = "dispense";break;
				default: invalid = true;
			}
		}
	}

	if(state[0]=='2'){
		if(!state.substr(1).compare("10")){
			switch (value) {
				case 10: state.replace(1,2,"20");break;
				case 20: state.replace(1,2,"30");break;
				case 50: state.replace(1,2,"60");break;
				default: invalid = true;
			}
		}else if(!state.substr(1).compare("20")){
			switch (value) {
				case 10: state.replace(1,2,"30");break;
				case 20: state.replace(1,2,"40");break;
				case 50: state.replace(1,2,"70");break;
				default: invalid = true;
			}
		}else if(!state.substr(1).compare("30")){
			switch (value) {
				case 10: state.replace(1,2,"40");break;
				case 20: state.replace(1,2,"50");break;
				case 50: state = "dispense";break;
				default: invalid = true;
			}
		}else if(!state.substr(1).compare("40")){
			switch (value) {
				case 10: state.replace(1,2,"50");break;
				case 20: state.replace(1,2,"60");break;
				case 50: state = "dispense";break;
				default: invalid = true;
			}
		}else if(!state.substr(1).compare("50")){
			switch (value) {
				case 10: state.replace(1,2,"60");break;
				case 20: state.replace(1,2,"70");break;
				case 50: state = "dispense";break;
				default: invalid = true;
			}
		}else if(!state.substr(1).compare("60")){
			switch (value) {
				case 10: state.replace(1,2,"70");break;
				case 20: ;
				case 50: state = "dispense";break;
				default: invalid = true;
			}
		}else if(!state.substr(1).compare("70")){
			switch (value) {
				case 10: ;
				case 20: ;
				case 50: state = "dispense";break;
				default: invalid = true;
			}
		}
	}

	//Handle Drink 3 for 100ct
	if(state[0]=='3'){
		if(!state.substr(1).compare("10")){
			switch (value) {
				case 10: state.replace(1,2,"20");break;
				case 20: state.replace(1,2,"30");break;
				case 50: state.replace(1,2,"60");break;
				default: invalid = true;
			}
		}else if(!state.substr(1).compare("20")){
			switch (value) {
				case 10: state.replace(1,2,"30");break;
				case 20: state.replace(1,2,"40");break;
				case 50: state.replace(1,2,"70");break;
				default: invalid = true;
			}
		}else if(!state.substr(1).compare("30")){
			switch (value) {
				case 10: state.replace(1,2,"40");break;
				case 20: state.replace(1,2,"50");break;
				case 50: state.replace(1,2,"80");break;
				default: invalid = true;
			}
		}else if(!state.substr(1).compare("40")){
			switch (value) {
				case 10: state.replace(1,2,"50");break;
				case 20: state.replace(1,2,"60");break;
				case 50: state.replace(1,2,"90");break;
				default: invalid = true;
			}
		}else if(!state.substr(1).compare("50")){
			switch (value) {
				case 10: state.replace(1,2,"60");break;
				case 20: state.replace(1,2,"70");break;
				case 50: state = "dispense";break;
				default: invalid = true;
			}
		}else if(!state.substr(1).compare("60")){
			switch (value) {
				case 10: state.replace(1,2,"70");break;
				case 20: state.replace(1,2,"80");break;
				case 50: state = "dispense";break;
				default: invalid = true;
			}
		}else if(!state.substr(1).compare("70")){
			switch (value) {
				case 10: state.replace(1,2,"80");break;
				case 20: state.replace(1,2,"90");break;
				case 50: state = "dispense";break;
				default: invalid = true;
			}
		}else if(!state.substr(1).compare("80")){
			switch (value) {
				case 10: state.replace(1,2,"90");break;
				case 20: ;
				case 50: state = "dispense";break;
				default: invalid = true;
			}
		}else if(!state.substr(1).compare("90")){
			switch (value) {
				case 10: ;
				case 20: ;
				case 50: state = "dispense";break;
				default: invalid = true;
			}
		}
	}





	// for all states and inputs which are not handled above show a message and return original state
	if (invalid)
		std::cout << "Invalid input.\n";

	return state;
}


int main(int argc, char * argv[])
{
	std::string state = "0";
	bool extendedMode = false;

	if(argc == 2)
		extendedMode = true;

	while(true)
	{
		int value = 0;
		std::string input;
		if(state == "0" && extendedMode)
			std::cout << "Current state: " << state << ". Please select a drink (1, 2, 3): ";
		else
			std::cout << "Current state: " << state << ". Please input a coin (10, 20, 50): ";
		std::getline(std::cin, input);
		std::stringstream(input) >> value;

		state = extendedMode ? stepExtended(state, value) : step(state, value);

		if(state == "dispense")
		{
			std::cout << "Here is your drink. Goodbye!\n\n";
			state = "0";
		}
	}

	return 0;
}
