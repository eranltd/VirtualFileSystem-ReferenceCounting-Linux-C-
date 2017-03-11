/*
 * Folder.h
 *
 *  Created on: Apr 1, 2016
 *      Author: eranpel
 */

#ifndef FOLDER_H_
#define FOLDER_H_
#include<list>
#include <memory>
#include<iostream>
#include<algorithm>
#include<vector>
#include "FileIO.h"
using namespace std;



struct BadFolder : public exception
{
  const char * what () const throw ()
  {
    return "ERROR : the directory already exist!";
  }
};

struct BadFolderNotFound : public exception
{
  const char * what () const throw ()
  {
    return "ERROR : the directory doesn't exist!";
  }
};

class Folder {

	private:

	string folderName;
	Folder* parent; //pointer to parent of current folder


	public:
	Folder(string foldername,Folder* parent = 0):folderName(foldername),parent(parent){}
	~Folder(){}

	Folder* findSubFolder(string findFolderName, vector<Folder>&check); //finds subFolder by string
	void pwd(Folder *findGparent); //prints working directory
	void mkdir(string subFolderName,const Folder& mainDirectory); //creates a new dir
	void chdir(string datapath,Folder*& pwd,const Folder& mainDirectory); //change the working directory
	vector<string> parseFolderPath(string pathName); //get path a parse him into vector
	void rmdir(string subFolderName,const Folder& mainDirectory); //finds dir and removes it
	void ls(string datapath,const Folder& mainDirectory); //prints the content of folder
	void lproot() ; //recursive show all contents
	void lprootrec(Folder *folder);
	string getFolderName()const{return folderName;}
	vector<Folder> subFolders;
	vector<FileIO> files;
};





#endif /* FOLDER_H_ */
