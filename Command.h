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

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include "Led.h"

using namespace std;

class Command {
private:
	string userInput;
	int current, end, lineAddress1=-1, lineAddress2=-1;
	char command = '0';
	void parseCommand();
	void removeWhiteSpaces();
	void replaceDot();
	void replaceDollar();
	int findComma();
	bool startingWithNumber();
	int charExists();
	bool endsWithAlpha();
	bool alphaNumeric();
	bool isNumber(string);
public:
	Command(string, int, int);
};
#endif // !COMMAND_H

