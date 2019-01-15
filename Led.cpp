//-----------------------------------------------
/**
* This class implements a command line text editor
* It takes input fileName as an input from driver.cpp
* It takes commands from the user and passes it to the Commmand class to parse the command

* @author  Mehakpreet Singh
* @version 1.0
* @since   2018-06-25
*/
//-----------------------------------------------

#include "Led.h"
#include "Command.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int Led::startIndex;
int Led::endIndex;
char Led::command;

Led::Led() {

}

//-----------------------------------------------
/*
	Constructor for the class takes "filename" as parameter	
	if the filename exists, it loads its contents into the buffer
*/
//-----------------------------------------------

Led::Led(string filename) {
	//if there is no file name
	if (filename.empty()) {
		cout << "\"?\" [New File]\nEntering Command Mode .\n";
		current = end = 0;
		command = '?';
		it = buffer.begin();
		bufferAltered = false;
	}
	else {
		ifstream fin(filename);
		fileName = filename;
		if (!fin) {		//	if the file doesn't exist
			cout << "\"" << filename << "\"" << " [New File]\nEntering Command Mode .\n";
			begin = current = end = 0;
		}
		else {
			int lineNum = 0;
			string line;
			while (getline(fin, line)) {
				++lineNum;
				buffer.push_back(line);
			}
			cout << "\"" << filename << "\" " << lineNum<<" lines\nEntering Command Mode .\n";
			begin = current = 1;
			end = lineNum;
			bufferAltered = false;

		}
	}
}

//-----------------------------------------------
/*
* This function is called from the main method using the
	object of LED class, and is responsible for performing
	all the operations of the text editor
*/
//-----------------------------------------------

void Led::run() {

	while (command != 'q') {
		cout << "? ";
		it = buffer.begin();
		string line;
		getline(cin, line);
		Command cmdObj(line, Led::current, Led::end);
		
		//cout << "1. " << startIndex << "\n2. " << endIndex << "\n3. " << command << endl;
		
		switch (command) {
		case 'e':
			cout << "INVALID COMMAND, TRY AGAIN"<<endl;
			break;
		case 'i':
			if (startIndex > buffer.size() || (startIndex == 0 && buffer.size() != 0)) {
				cout << "Invalid range\n";
				break;
			}
			else {
				insert();
				break;
			}
		case 'a':
			if (buffer.size() == 0)
				cout << "empty buffer\n";
			else if (startIndex > buffer.size()) {
				cout << "Invalid range\n";
			}
			else {
				append();
			}
			break;
		case 'g':
			if (buffer.size() == 0)
				cout << "empty buffer\n";
			else if(startIndex > buffer.size())
				cout << "Invalid range\n";
			else
				current = startIndex;
			break;
		case 'p':
			if (buffer.size() == 0)
				cout << "empty buffer\n";
			else if (startIndex > buffer.size() || endIndex > buffer.size() || endIndex < startIndex)
				cout << "Invalid range\n";
			else {
				print();
			}
			break;
		case 'd':
			if (buffer.size() == 0)
				cout << "empty buffer\n";
			else if (startIndex > buffer.size() || endIndex > buffer.size() || endIndex < startIndex)
				cout << "Invalid range\n";
			else {
				erase();
			}
			break;
		case '+':
			if (buffer.size() == 0)
				cout << "empty buffer\n";
			else if (current + startIndex <= buffer.size())
				current += startIndex;
			else if(current + startIndex > buffer.size())
				cout<<"End of file reached\n";
			else
				cout << "Invalid range\n";
			break;
		case '-':
			if (buffer.size() == 0)
				cout << "empty buffer\n";
			else if (current - startIndex > 0)
				current -= startIndex;
			else if (current - startIndex <= 0)
				cout << "Top of file reached\n";
			else
				cout << "Invalid range\n";
			break;
		case 'r':
			if (buffer.size() == 0)
				cout << "empty buffer\n";
			else if (startIndex > buffer.size() || endIndex > buffer.size() || endIndex < startIndex)
				cout << "Invalid range\n";
			else {
				erase();
				insert();
			}
			break;
		case 'j':
			if (buffer.size() == 0)
				cout << "empty buffer\n";
			else if (startIndex > buffer.size() || endIndex > buffer.size() || endIndex < startIndex)
				cout << "Invalid range\n";
			else {
				join();
			}
			break;
		case 'c':
			if (buffer.size() == 0)
				cout << "empty buffer\n";
			else if (startIndex > buffer.size() || endIndex > buffer.size() || endIndex < startIndex)
				cout << "Invalid range\n";
			else {
				change();
			}
			break;
		case 'x':
			if (buffer.size() == 0)
				cout << "empty buffer\n";
			else if (startIndex > buffer.size() || endIndex > buffer.size() || endIndex < startIndex)
				cout << "Invalid range\n";
			else {
				cut();
			}
			break;
		case 'v':
			if (buffer.size() == 0)
				cout << "empty buffer\n";
			else if (startIndex > buffer.size() || endIndex > buffer.size() || endIndex < startIndex)
				cout << "Invalid range\n";
			else {
				startIndex++;
				paste();
			}
			break;
		case 'u':
			if (buffer.size() == 0)
				cout << "empty buffer\n";
			else if (startIndex > buffer.size() || endIndex > buffer.size() || endIndex < startIndex)
				cout << "Invalid range\n";
			else {
				paste();
			}
			break;
		case 'w':
			if (bufferAltered) {
				writeToFile();
			}
			bufferAltered = false;
			break;
		case 'q':
			string choice;
			if (bufferAltered) {
				cout << "save changes to file (y/n)? ";
				getline(cin, choice);
				while (!correctChoice(choice)) {
					cout << "bad answer: " << choice;
					cout << "\nEnter y for yes and n for no.";
				}
				if (correctChoice(choice) == 1) {
					writeToFile();
				}
				else if (correctChoice(choice) == 2) {
				}
			}
			cout << "Bye\n";
			break;
		}
		cin.clear();
	}	
}

//-----------------------------------------------
/*
* The following three functions sets the value of the
	static variables startIndex, endIndex, and command,
	once the command has been read and parsed by the 
	command class

* @param  val, value forwarded by the command class

*/
//-----------------------------------------------
void Led::setStartIndex(int val) {
	Led::startIndex = val;
}

void Led::setEndIndex(int val) {
	Led::endIndex = val;
}

void Led::setCommand(char val) {
	Led::command = val;
}

//-----------------------------------------------
/*
* Appends the text below the startIndex
*/
//-----------------------------------------------
void Led::append() {
	string line;
	advance(it, startIndex);
	current = startIndex;
	while (getline(cin, line)) {
		buffer.insert(it, line);
		current++;
		end++;
	}
	bufferAltered = true;
	cin.clear();
}

//-----------------------------------------------
/*
* inserts the text above the startIndex
*/
//-----------------------------------------------
void Led::insert() {
	string line;
	it = buffer.begin();
	current = startIndex;
	if (startIndex != 0)
		advance(it, startIndex - 1);
	else
		current = 1;
	while (getline(cin, line)) {
		buffer.insert(it, line);
		current++;
		end++;
	}
	current--;
	bufferAltered = true;
	cin.clear();
}

//-----------------------------------------------
/*
* prints the contents of the buffer on console,
	between the start and end index
*/
//-----------------------------------------------
void Led::print() {
	int beg = startIndex;
	advance(it, startIndex - 1);
	for (int i = 0; i <= (endIndex - startIndex); ++i) {
		cout << beg;
		if (beg == current)
			cout << "> ";
		else
			cout << ": ";
		cout << *it << "\n";
		it++;
		beg++;
	}
}

//-----------------------------------------------
/*
* erases the contents of the buffer,
	between the start and end index
*/
//-----------------------------------------------
void Led::erase() {
	it = buffer.begin();
	advance(it, startIndex - 1);
	current = startIndex;
	for (int i = 0; i <= (endIndex - startIndex); ++i) {
		it = buffer.erase(it);
		end--;
	} 
	if (it == buffer.end()) {
		current--;
	}
	bufferAltered = true;
}

//-----------------------------------------------
/*
* checks whether the choice entered by user is
  either 'yes' or 'no' and nothing other than that.
*/
//-----------------------------------------------
int Led::correctChoice(string choice) {
	if (choice.size() == 1 && (choice[0] == 'y' || choice[0] == 'Y')) {
		return 1;
	}
	else if (choice.size() == 1 && (choice[0] == 'n' || choice[0] == 'N')) {
		return 2;
	}
	else {
		return 0;
	}
}

//-----------------------------------------------
/*
* write the unsaved changes in the buffer to the file 
*/
//-----------------------------------------------
void Led::writeToFile() {
	ofstream fout;
	if (fileName.empty()) {
		do {
			cout << "Enter a file name: ";
			getline(cin, fileName);
			fout.open(fileName);
		} while (!fout.is_open());
	}
	else {
		fout.open(fileName);
	}

	it = buffer.begin();
	for (it; it != buffer.end(); it++) {
		fout << *it;
		if (next(it,1) != buffer.end())
			fout << "\n";
	}
	cout << end << " lines written to file: \"" << fileName<<"\"\n";
}

//-----------------------------------------------
/*
* joins the contents of the buffer on console,
between the start and end index
*/
//-----------------------------------------------
void Led::join() {
	string joined;
	advance(it, startIndex - 1);
	current = startIndex;
	for (int i = 0; i <= (endIndex - startIndex); ++i) {
		joined = joined.append(*it).append(" ");
		it++;;
	}
	it = buffer.begin();
	advance(it, startIndex - 1);
	buffer.insert(it, joined);
	startIndex++;
	erase();
	current = startIndex - 1;
	bufferAltered = true;
}

//-----------------------------------------------
/*
* changes the specified substring to a new Value,
between the start and end index
*/
//-----------------------------------------------
void Led::change() {
	string toChange, change, line;
	int counter = 0;
	size_t pos = 0;
	cout << setw(13) << right << "Change what? ";
	getline(cin, toChange);
	cout << setw(13) << right << "To what? ";
	getline(cin, change);

	advance(it, startIndex - 1);
	current = startIndex;
	for (int i = 0; i <= (endIndex - startIndex); ++i) {
		line = *it;
		while (line.find(toChange, pos) != std::string::npos) {
			pos = line.find(toChange, pos);
			line.replace(pos, toChange.length(), change);
			pos += change.length();
			counter++;
		}
		pos = 0;
		*it = line;
		it++;;
	}
	cout << "Changed " << counter << " occurrence(s)" << endl;
	bufferAltered = true;
}

//-----------------------------------------------
/*
* erases the contents of the buffer
between the start and end index and
copies them to the clipboard
*/
//-----------------------------------------------
void Led::cut() {
	clipboard.clear();
	advance(it, startIndex - 1);
	current = startIndex;
	for (int i = 0; i <= (endIndex - startIndex); ++i) {
		clipboard.push_back(*it);
		it++;
	}
	erase();
}

//-----------------------------------------------
/*
* pastes the contents of the clipboard at the startIndex
*/
//-----------------------------------------------
void Led::paste() {
	advance(it, startIndex - 1);
	current = startIndex;
	for (int i = 0; i < clipboard.size(); i++) {
		buffer.insert(it, clipboard[i]);
		end++;
		current++;
	}
	current--;
	bufferAltered = true;
	clipboard.clear();
}