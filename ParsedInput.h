/*
 * ParsedInput.h
 *
 *  Created on: Mar 28, 2016
 *      Author: eranpel
 */

#ifndef PARSEDINPUT_H_
#define PARSEDINPUT_H_
//*This class gets a string and parse him to commands and arguments

#include<sstream>
#include<vector>
#include<iterator>
#include <algorithm>
using namespace std;

struct ParsedInput {
	string command; //holds the command to execute
	vector<string> arguments; //container of strings(arguments)
	vector<string>path;
	vector<string>path_dst;
	ParsedInput(string stringToParse)
	{
		//parsing the line into command arguments
		istringstream iss(stringToParse);
		getline(iss, command, ' '); //get the first word meaning "command"

		// get the other arguments
		// work
			string eachWord;
		   while(getline(iss, eachWord, ' '))
		   {
			   arguments.push_back(eachWord);
		   }
		   std::transform(command.begin(), command.end(), command.begin(), ::tolower); //convert to commandonly lowercase
		   if(arguments.size()>0)
		   {
			   path = parseFilePath(arguments[0]);
			   if(arguments.size()>1)
			   path_dst = parseFilePath(arguments[1]);
		   }
	}


	vector<string> parseFilePath(string pathName)
				{
			//gets /V/tmp format
			//and returns vector of directories without '/' sign.
							vector<string> directories;
							//parsing the line into directories
							istringstream iss(pathName);

								string eachWord;
							   while(getline(iss, eachWord, '/'))
							   {
								   directories.push_back(eachWord);
							   }
							   return directories;
		}
};

#endif /* PARSEDINPUT_H_ */
