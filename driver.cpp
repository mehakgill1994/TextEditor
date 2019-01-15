//-----------------------------------------------
/**
*
* This is a driver file to test LED

* LED stands for Line oriented Editor that allows
* users to open, edit and save new or existing files.
*
* @author  Mehakpreet Singh
* @version 1.0
* @since   2018-06-25
*/
//-----------------------------------------------

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
#include "Led.h"

int main(int argc, char * argv[]) {
	string filename;	//an empty filename
	switch (argc) {		//determine the filename
	case 1: //no file name
		break;
	case 2:
		filename = argv[1];		//initialize filename from argument
		break;
	default:
		cout << ("too many arguments - all discarded\n");
		break;
	}

	Led editor(filename);		//	create a Led named editor
	editor.run();				//	run the editor
	
	return 0;					//	report success
}