/*
 * Terminal.cpp
 *
 *  Created on: Mar 28, 2016
 *      Author: eranpel
 */
#include "Terminal.h"
#include "ParsedInput.h"
#include "Folder.h"



void Terminal::printHelp()
{
	cout <<"	This is a list of available commands:\n" <<endl;
	cout << "Please Note! the char counting starts from 0!"<<endl;
	cout <<"[1]	read FILENAME POSITION"<<endl;
	cout <<"[2]	write FILENAME POSITION CHARACTER"<<endl;
	cout <<"[3]	touch FILENAME"<<endl;
	cout <<"[4]	copy SOURCE_FILENAME TARGET_FILENAME"<<endl;
	cout <<"[5]	remove FILENAME"<<endl;
	cout <<"[6]	move SOURCE_FILENAME TARGET_FILENAME"<<endl;
	cout <<"[7]	cat FILENAME"<<endl;
	cout <<"[8]	wc FILENAME"<<endl;
	cout <<"[9]	ln TARGET_FILENAME LINK_NAME"<<endl;
	cout <<"[10]	mkdir FOLDERNAME"<<endl;
	cout <<"[11]	chdir FOLDERNAME"<<endl;
	cout <<"[12]	rmdir FOLDERNAME"<<endl;
	cout <<"[13]	ls FOLDERNAME"<<endl;
	cout <<"[14]	lproot"<<endl;
	cout <<"[15]	pwd"<<endl;
	cout <<"[16]	exit"<<endl;
}

void Terminal::start(){

	string stringToParse;
	cout << "Hello There, for more info type 'help'"<<endl;

	while(true)
	{
		getline(cin,stringToParse,'\n'); //if we used cin <<stringToParse it will read until the first '\n' so we need to read the entire line
		ParsedInput data(stringToParse);
		Execute(data); //execute the method related to command
	}
}

FileIO* Terminal::findlnFile(string findLnName, vector<FileIO>&check)
{
	for(int i=0;i<(int)check.size();i++)
	{
		if(findLnName == check[i].getFileName())return &check[i];
	}
	return 0;
}


void Terminal::read(string filename,int position)
{
	FileIO* found_ln = findlnFile(filename,hardLinks);
	fstream::pos_type i = position;
	if(found_ln)
	{
		cout <<found_ln->operator [](i) <<endl;
	}
	else
	{
		FileIO myfile(filename);
		cout <<myfile[i] <<endl;
	}
}

void Terminal::write(string filename,int position,char character){
		FileIO* found_ln = findlnFile(filename,hardLinks);
		fstream::pos_type i = position;
		if(found_ln)
			{
			found_ln->operator [](i) = character;
			}
			else
			{
				FileIO myfile(filename);
				myfile[i] = character;
			}
}

void Terminal::touch(string filename)
{

	FileIO myfile(filename);
	myfile.touch();
	currentWorkingDirectory->files.push_back(myfile);
}

void Terminal::copy(string src_filename,string dst_filename)
{
	FileIO* found_name = findlnFile(src_filename,hardLinks);
	if(found_name)
	{
		found_name->copy(dst_filename);
		FileIO dst_file(dst_filename);
		mainDirectory.files.push_back(dst_file);
	}
	else
	{
		FileIO src_file(src_filename);
		src_file.copy(dst_filename);
		FileIO dst_file(dst_filename);
		mainDirectory.files.push_back(dst_file);
	}

}

void Terminal::move(string src_filename,string dst_filename)
{
	FileIO src_file(src_filename);
	src_file.move(dst_filename);
}



void Terminal::remove(string filename){FileIO removeMe(filename);removeMe.remove();}
int Terminal::stringToCommandNumber(ParsedInput parsedInput){
	if(parsedInput.command == "help")return 0;
	if(parsedInput.command == "read")return 1;
	if(parsedInput.command == "write")return 2;
	if(parsedInput.command == "touch")return 3;
	if(parsedInput.command == "copy")return 4;
	if(parsedInput.command == "remove")return 5;
	if(parsedInput.command == "move")return 6;
	if(parsedInput.command == "cat")return 7;
	if(parsedInput.command == "wc")return 8;
	if(parsedInput.command == "ln")return 9;
	if(parsedInput.command == "mkdir")return 10;
	if(parsedInput.command == "chdir")return 11;
	if(parsedInput.command == "rmdir")return 12;
	if(parsedInput.command == "ls")return 13;
	if(parsedInput.command == "lproot")return 14;
	if(parsedInput.command == "pwd")return 15;
	if(parsedInput.command == "exit")return 16;
	return -1;

}

void Terminal::Execute(ParsedInput parsedInput)
{
	try{
		switch ( (stringToCommandNumber(parsedInput)) ) //convert the command to int to trigger the right command
		{
		case 0:
			printHelp();
			return;
		case 1:
			if(parsedInput.arguments.size()<2)throw BadData();
			read(parsedInput.path[parsedInput.path.size()-1],atoi(parsedInput.arguments[1].c_str()));
			return;
		case 2:
			if(parsedInput.arguments.size()<3)throw BadData();
			write(parsedInput.path[parsedInput.path.size()-1],atoi(parsedInput.arguments[1].c_str()),parsedInput.arguments[2][0]);
			return;
		case 3:
			if(parsedInput.arguments.size()<1)throw BadData();
			touch(parsedInput.path[parsedInput.path.size()-1]);
			return;
		case 4:
			if(parsedInput.arguments.size()<2)throw BadData();
				copy(parsedInput.path[parsedInput.path.size()-1], parsedInput.path_dst[parsedInput.path.size()]);
			return;
		case 5:
			if(parsedInput.arguments.size()<1)throw BadData();
			remove(parsedInput.arguments[0]);
			return;
		case 6:
			if(parsedInput.arguments.size()<2)throw BadData();
			move(parsedInput.arguments[0],parsedInput.arguments[1]);
			return;
		case 7:
			if(parsedInput.arguments.size()<1)throw BadData();
			cat(parsedInput.path[parsedInput.path.size()-1]);
			return;
		case 8:
			if(parsedInput.arguments.size()<1)throw BadData();
			wc(parsedInput.arguments[0]);
			return;
		case 9:
			if(parsedInput.arguments.size()<1)throw BadData();
			ln(parsedInput.arguments[0],parsedInput.arguments[1]);
			return;

		case 10:
			if(parsedInput.arguments.size()<1)throw BadData();
			mkdir(parsedInput.arguments[0],mainDirectory);
			return;

		case 11:
			if(parsedInput.arguments.size()<1)throw BadData();
			chdir(parsedInput.arguments[0],currentWorkingDirectory,mainDirectory);
			return;
		case 12:
			if(parsedInput.arguments.size()<1)throw BadData();
			rmdir(parsedInput.arguments[0],mainDirectory);
			return;
		case 13:
			if(parsedInput.arguments.size()<1)throw BadData();
			ls(parsedInput.arguments[0],mainDirectory);
			return;
		case 14:
			lproot();
			return;
		case 15:
			pwd();
		return;

		case 16:
			cout << "Have a nice day\n";
			exit(1);
		default:
			throw BadData();
		}

	}
	catch(exception &err)
	{
		cout << err.what() <<endl;
	}

}
void Terminal::cat(string filename)
{
	FileIO* found_ln = findlnFile(filename,hardLinks);
	if(found_ln){
		found_ln->cat();
	}
	else
	{
	FileIO src_file(filename);
	src_file.cat();
	}
}

void Terminal::wc(string filename)
{
	FileIO* found_ln = findlnFile(filename,hardLinks);
	if(found_ln){
		found_ln->wc();
	}
	else
	{
	FileIO src_file(filename);
	src_file.wc();
	}
}

void Terminal::ln(string fileName, string linkName){

	FileIO result(fileName); //create instance to file
	result.checkFile();
	result.setFileName(linkName); //with a different name
	hardLinks.push_back(result);
}

