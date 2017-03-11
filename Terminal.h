/*
 * Terminal.h
 *
 *  Created on: Mar 28, 2016
 *      Author: eranpel
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_
#include"FileIO.h"
#include "Folder.h"
#include "ParsedInput.h"
#include <string>
#include <iostream>
#include <list>


struct BadData : public exception
{
  const char * what () const throw ()
  {
    return "Unknown command!,please try again!";
  }
};



class Terminal {
private:
	 Folder mainDirectory; //root of all sub directories and files
	 Folder *currentWorkingDirectory; //pointer to the pwd

	public:
	vector<FileIO>hardLinks; //will hold the hardlinks to files
	Terminal():mainDirectory("V"){currentWorkingDirectory = &mainDirectory;}
	virtual ~Terminal(){} //no need for d'tor we are using STL for storing our objects
	void printHelp(); //prints the manual for program
	void start(); //the main REPL running until "exit" has been entered

	void Execute(ParsedInput parsedInput); //gets input from user and calls the right command //the switch case menu
	int stringToCommandNumber(ParsedInput parsedInput); //convert the command to int to trigger the right command
	FileIO* findlnFile(string findLnName, vector<FileIO>&check); //search for ln file
	void read(string filename,int position);//read one char from file
	void write(string filename,int position,char character);//updates one char in the file with char
	void touch(string filename); //updates file time_sign or creates a new one
	void copy(string src_filename,string dst_filename); //copy from one file to another
	void remove(string filename); //deletes the file
	void move(string src_filename,string dst_filename); //move the file
	void cat(string filename);//prints the file content
	void wc(string filename);  //prints the number of lines inside the file
	void ln(string target_filename,string linkName); //hard-link to files method


	vector<string>parseFolderPath(string pathName); //helping method

	void mkdir(string folderName,const Folder &root){mainDirectory.mkdir(folderName,root);}//creates a new folder
	void chdir(string folderName,Folder* pwd,const Folder &root){mainDirectory.chdir(folderName,currentWorkingDirectory,root);}//change the current folder
	void rmdir(string folderName,const Folder &root){mainDirectory.rmdir(folderName,root);}//deletes a folder
	void ls(string folderName,Folder &root){mainDirectory.ls(folderName,root);}//prints the contents of the current directory
	void lproot(){cout << "HardLinks are: \n";for(int i=0;i<(int)hardLinks.size();i++){cout << hardLinks[i].getFileName()<<'\n';}mainDirectory.lproot();} //prints all files and folder in the virtual drive
	void pwd(){mainDirectory.pwd(currentWorkingDirectory);} //prints working path inside virtual drive


};

#endif /* TERMINAL_H_ */
