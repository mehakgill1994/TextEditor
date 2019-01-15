//-----------------------------------------------
/**
* This is a header file for the Led.cpp which implements a command line text editor
* It takes input fileName as an input from driver.cpp
* It takes commands from the user and passes it to the Commmand class to parse the command

* @author  Mehakpreet Singh
* @version 1.0
* @since   2018-06-25
*/
//-----------------------------------------------

#ifndef LED_H
#define LED_H

#include <string>
#include <list>
#include <iterator>
#include <iomanip>
#include <vector>
using namespace std;

class Led {

private:
	list<string> buffer;
	vector<string> clipboard;
	list<string>::iterator it;
	int begin, current, end;
	static int startIndex, endIndex;		//range index of the given command
	static char command;					//the command entered by user
	string fileName;
	bool bufferAltered;
	void insert();
	void append();
	void print();
	void erase();
	int correctChoice(string);
	void writeToFile();
	void join();
	void change();
	void cut();
	void paste();
public:
	Led();				//	default constructor
	Led(string);		//	constructor
	void run();
	void setStartIndex(int);
	void setEndIndex(int);
	void setCommand(char);
};
#endif // !1
