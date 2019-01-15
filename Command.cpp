//-----------------------------------------------
/**
* This is a header file for Command.cpp which parses the commands input by user in LED
* It takes in input a command, end index of file and current index of file.
* It parses the command and passes the name of the command,
* the start and end range mentioned in the command back to the LED class

* @author  Mehakpreet Singh
* @version 1.0
* @since   2018-06-25
*/
//-----------------------------------------------

#include "Command.h"


//-----------------------------------------------
/*
* The constructor for the class

* @param  userInput, sets the value of user input to parse
* @param  current, current index in the buffer
* @param  userInput, end index in the buffer

*/
//-----------------------------------------------
Command::Command(string userInput, int current, int end) {
	this->userInput = userInput;
	this->current = current;
	this->end = end;
	parseCommand();
}

//-----------------------------------------------
/*
* The main function responsible to parse the command entered by the user
*/
//-----------------------------------------------
void Command::parseCommand() {
	removeWhiteSpaces();
	replaceDot();
	replaceDollar();
	
	if (userInput.size() == 0) {		//if empty userInput is passed,
		lineAddress1 = 1;					// increment the current position by one
		lineAddress2 = 1;
		command = '+';
	}
	else if (userInput.size() == 1) {	//if the length of userInput is 1
		if (isdigit(userInput[0])) {		//if that one char is numeric, change the current position to that value
			lineAddress1 = stoi(userInput);
			lineAddress2 = stoi(userInput);
			command = 'g';
		}
		else if (isalpha(userInput[0])) {	//if that one char is alpha, the command is either 'w', 'i', 'p' or 'q'
			lineAddress1 = 0;
			lineAddress2 = 0;
			if (userInput[0] == 'q')
				command = 'q';
			else if (userInput[0] == 'w')
				command = 'w';
			else if (userInput[0] == 'i') {
				command = 'i';
				lineAddress1 = lineAddress2 = current;
			}
			else if (userInput[0] == 'p') {
				command = 'p';
				lineAddress1 = lineAddress2 = current;
			}
			else if (userInput[0] == 'a') {
				command = 'a';
				lineAddress1 = lineAddress2 = current;
			}
			else if (userInput[0] == 'v') {
				command = 'v';
				lineAddress1 = lineAddress2 = current;
			}
			else if (userInput[0] == 'u') {
				command = 'u';
				lineAddress1 = lineAddress2 = current;
			}
			else if (userInput[0] == 'd') {
				command = 'd';
				lineAddress1 = lineAddress2 = current;
			}
			else if (userInput[0] == 'x') {
				command = 'x';
				lineAddress1 = lineAddress2 = current;
			}
			else if (userInput[0] == 'r') {
				command = 'r';
				lineAddress1 = lineAddress2 = current;
			}
			else if (userInput[0] == 'j') {
				command = 'j';
				lineAddress1 = lineAddress2 = current;
			}
			else if (userInput[0] == 'c') {
				command = 'c';
				lineAddress1 = lineAddress2 = current;
			}
			else if (userInput[0] == 'g') {
				command = 'g';
				lineAddress1 = lineAddress2 = current;
			}
			else
				command = 'e';				//'e' refers to invalid command
		}
		else if (userInput[0] == '+') {
			lineAddress1 = 1;					// increment the current position by one
			lineAddress2 = 1;
			command = '+';
		}
		else if (userInput[0] == '*') {			//print the entire buffer
			lineAddress1 = 1;					
			lineAddress2 = end;
			command = 'p';
		}
		else if (userInput[0] == '.') {		//print the current line
			lineAddress1 = current;					
			lineAddress2 = current;
			command = 'p';
		}
		else if (userInput[0] == '$') {		//print the last line
			lineAddress1 = end;
			lineAddress2 = end;
			command = 'p';
		}
		else if (userInput[0] == '-') {
			lineAddress1 = 1;					// decrement the current position by one
			lineAddress2 = 1;
			command = '-';
		}
		else
			command = 'e';				//'e' refers to invalid command
	}
	else {	//userInput is more than one character long
		if (findComma() == -2 || charExists() > 1) {		//more than one comma's or characters in the userInput
			command = 'e';
		}
		else if (!alphaNumeric()){							//if userInput contains something other than digits and alphabets
			if (userInput[userInput.size() - 1] == '+') {
				string str = userInput.substr(0, userInput.size() - 1);
				if (isNumber(str)) {
					lineAddress2 = lineAddress1 = stoi(str);
					command = '+';
				}
				else
					command = 'e';
			}
			else if (userInput[userInput.size() - 1] == '-') {
				string str = userInput.substr(0, userInput.size() - 1);
				if (isNumber(str)) {
					lineAddress2 = lineAddress1 = stoi(str);
					command = '-';
				}
				else
					command = 'e';
			}
			else
				command = 'e';
		}
		else if (charExists() == 1 && endsWithAlpha()) {		//number of characters in userInput is equal to 1
			command = userInput[userInput.size() - 1];		//and it ends with char
			if (command == 'g' || command == 'a' || command == 'i' || command == 'v' || command == 'u') {
				if (userInput.size() != 2)
					command = 'e';
				else {
					lineAddress1 = lineAddress2 = stoi(userInput.substr(0, userInput.size() - 1));
				}
			}
			else {
				if (findComma() == -1) {			//if comma doesn't exist
					string str = userInput.substr(0, userInput.size() - 1);
					lineAddress2 = lineAddress1 = stoi(str);
				}
				else {								//comma exists
					if (findComma() == 0) {								//comma is in the beginning, no 'x' value
						string str = userInput.substr(1, userInput.size() - 2);
						lineAddress1 = current;
						lineAddress2 = stoi(str);
					}
					else if (findComma() == (userInput.size() - 2)) {	//comma is just before the command, no 'y' value
						string str = userInput.substr(0, userInput.size() - 2);
						lineAddress2 = current;
						lineAddress1 = stoi(str);
					}
					else {												//both 'x' and 'y' values exist
						string str1 = userInput.substr(0, findComma());
						string str2 = userInput.substr(findComma() + 1);
						str2 = str2.substr(0, str2.size() - 1);
						lineAddress1 = stoi(str1);
						lineAddress2 = stoi(str2);
					}
				}
			}
		}
		else if (charExists() == 0) {		//command doesn't exists
			if (findComma() == -1) {			//if comma doesn't exist
				lineAddress2 = lineAddress1 = stoi(userInput);
				command = 'g';
			}
			else {								//comma exists
				command = 'p';
				if (findComma() == 0) {								//comma is in the beginning, no 'x' value
					string str = userInput.substr(1);
					lineAddress1 = current;
					lineAddress2 = stoi(str);
				}
				else if (findComma() == (userInput.size() - 1)) {	//comma is at the end, no 'y' value
					string str = userInput.substr(0, userInput.size() - 1);
					lineAddress2 = current;
					lineAddress1 = stoi(str);
				}
				else {												//both 'x' and 'y' values exist
					string str1 = userInput.substr(0, findComma());
					string str2 = userInput.substr(findComma() + 1);
					lineAddress1 = stoi(str1);
					lineAddress2 = stoi(str2);
				}
			}
		}
		else
			command = 'e';
	}

	//passing the parsed command back to Led
	Led ledObj;
	//if (!(lineAddress1 > 0 || lineAddress2 > 0))
		//command = 'e';
	ledObj.setStartIndex(lineAddress1);
	ledObj.setEndIndex(lineAddress2);
	ledObj.setCommand(command);
}


//-----------------------------------------------
/*
* check if the comma exists in user input,
	if yes, then retun the position where it exists
	if no, return -1

	@return int, the position of comma
*/
//-----------------------------------------------
int Command::findComma() {
	int count = 0;
	int index;
	for (int i = 0; i < userInput.size(); i++) {
		if (userInput[i] == ',') {
			index = i;
			count++;
		}		
	}
	if (count == 1)
		return index;		//index of the comma
	else if (count == 0)
		return -1;			//no comma exists
	else
		return -2;			//more than one comma's exists
}

//-----------------------------------------------
/*
* remove all white spaces in the user input
*/
//-----------------------------------------------
void Command::removeWhiteSpaces() {
	string::iterator it = userInput.begin();
	while (it != userInput.end()) {
		if (*it == ' ') {
			userInput.erase(it);
		}
		else {
			it++;
		}
	}
}

//-----------------------------------------------
/*
* replaces all occurrences of '.' with the current index
*/
//-----------------------------------------------
void Command::replaceDot() {
	if (userInput.size() > 1) {
		for (int i = 0; i < userInput.size(); i++) {
			if (userInput[i] == '.')
				userInput[i] = current;
		}
	}
}

//-----------------------------------------------
/*
* replaces all occurrences of '$' with the last index
*/
//-----------------------------------------------
void Command::replaceDollar() {
	if (userInput.size() > 1) {
		for (int i = 0; i < userInput.size(); i++) {
			if (userInput[i] == '$')
				userInput[i] = end;
		}
	}
}

//-----------------------------------------------
/*
* check if the command starts with a number,

@return bool, true/false
*/
//-----------------------------------------------
bool Command::startingWithNumber() {
	if (isdigit(userInput[0]))
		return true;
	return false;
}

//-----------------------------------------------
/*
* check if a char exists in user input,
if yes, then retun the number of occurrences of the same
if no, return 0

@return int, number of characters
*/
//-----------------------------------------------
int Command::charExists() {
	int count = 0;
	for (int i = 0; i < userInput.size(); i++) {
		if (isalpha(userInput[i]))
			count++;
	}
	return count;
}

//-----------------------------------------------
/*
* check if the command ends with a alphabet,

@return bool, true/false
*/
//-----------------------------------------------
bool Command::endsWithAlpha() {
	return isalpha(userInput[userInput.size() - 1]);
}

//-----------------------------------------------
/*
* check if the command doesn't contain anything
	other than alpha-numeric characters

@return bool, true/false
*/
//-----------------------------------------------
bool Command::alphaNumeric() {
	for (int i = 0; i < userInput.size(); i++) {
		if (!isalnum(userInput[i]))
			if (userInput[i] != ',')
				return false;
	}
	return true;
}

//-----------------------------------------------
/*
* check if the command consists of all digits
	and nothing else

@return bool, true/false
*/
//-----------------------------------------------
bool Command::isNumber(string input) {
	for (int i = 0; i < input.size(); i++) {
		if (!isdigit(input[i]))
				return false;
	}
	return true;
}