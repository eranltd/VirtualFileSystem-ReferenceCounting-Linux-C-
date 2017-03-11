/*
 * Folder.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: eranpel
 */

#include "Folder.h"

Folder* Folder::findSubFolder(string findFolderName, vector<Folder>&check)
{
	for(int i=0;i<(int)check.size();i++)
	{
		if(findFolderName == check[i].folderName)return &check[i];
	}
	return 0;
}

void Folder::pwd(Folder *findGparent)
{
	list<string>pwd;
	while(findGparent!=0)
	{
		pwd.push_front(findGparent->folderName);
		findGparent = findGparent->parent;
	}

	ostream_iterator<string> out(cout,"/");
	copy(pwd.begin(),pwd.end(),out);
}

void Folder::mkdir(string subFolderName,const Folder& mainDirectory){
	vector<string> fullPathtoCreate = parseFolderPath(subFolderName);
	Folder* check = const_cast<Folder*> (&mainDirectory); //pointer to the root of folders!
	//check->subFolders.push_back(Folder("eran"));
	Folder* foundSubFolder;
	if(fullPathtoCreate[0] == check->folderName && fullPathtoCreate.size()==1)throw BadFolder(); //firstcasE

	/****************************************************************************************************/

	for(int i=1 ; i<(int)fullPathtoCreate.size()-1 ; i++) //from 1-n(because [0] is the root name
	{
		foundSubFolder  = findSubFolder(fullPathtoCreate[i],check->subFolders);
		if(foundSubFolder)check = foundSubFolder;
		else
			throw BadFolderNotFound();
	}


	cout << "FolderCreated Successfuly at: "<<check->folderName <<endl;
	//check if the last level contains folder
	Folder *checkLastLevel = findSubFolder(fullPathtoCreate[fullPathtoCreate.size()-1],check->subFolders);
	if(checkLastLevel!=0)throw BadFolder();


	check->subFolders.push_back(Folder(fullPathtoCreate[fullPathtoCreate.size()-1],check));

}

void Folder::rmdir(string subFolderName,const Folder& mainDirectory)
{
	vector<string> fullPathtoCreate = parseFolderPath(subFolderName);
	Folder* check = const_cast<Folder*> (&mainDirectory); //pointer to the root of folders!
	Folder* foundSubFolder;

	/****************************************************************************************************/

	for(int i=1 ; i<(int)fullPathtoCreate.size()-1 ; i++) //from 1-n(because [0] is the root name
	{
		foundSubFolder  = findSubFolder(fullPathtoCreate[i],check->subFolders);
		if(foundSubFolder)check = foundSubFolder;
		else
			throw BadFolderNotFound();
	}


	for(std::vector<Folder>::iterator it = check->subFolders.begin(); it != check->subFolders.end(); ++it) {
		if(fullPathtoCreate[fullPathtoCreate.size()-1] == it->folderName)
		{
			check->subFolders.erase(it);
			cout << "FolderRemoved Successfuly at: "<<check->folderName <<endl;
			return ;
		}

	}
}
vector<string> Folder::parseFolderPath(string pathName)
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

void Folder::chdir(string datapath,Folder*& pwd,const Folder& mainDirectory)
{
	vector<string> fullPathtoFind = parseFolderPath(datapath);
	Folder* check = const_cast<Folder*> (&mainDirectory); //pointer to the root of folders!
	//check->subFolders.push_back(Folder("eran"));
	Folder* foundSubFolder;
	if(fullPathtoFind[0] == check->folderName && fullPathtoFind.size()==1)return; //firstcasE
	/****************************************************************************************************/

	for(int i=1 ; i<(int)fullPathtoFind.size()-1 ; i++) //from 1-n(because [0] is the root name
	{

		foundSubFolder  = findSubFolder(fullPathtoFind[i],check->subFolders);
		if(foundSubFolder)
		{
			check = foundSubFolder;
		}
		else
			throw BadFolderNotFound();
	}
	Folder *foundLastLevel =  findSubFolder(fullPathtoFind[fullPathtoFind.size()-1],check->subFolders);

	if(foundLastLevel!=0)
	{
		pwd = foundLastLevel;
	}
	else
	{
		throw BadFolderNotFound();
	}
}

void Folder::ls(string datapath,const Folder& mainDirectory)
{
	vector<string> fullPathtoFind = parseFolderPath(datapath);
	Folder* check = const_cast<Folder*> (&mainDirectory); //pointer to the root of folders!
	Folder* foundSubFolder;
	for(int i=1 ; i<(int)fullPathtoFind.size()-1 ; i++) //from 1-n(because [0] is the root name
	{

		foundSubFolder  = findSubFolder(fullPathtoFind[i],check->subFolders);
		if(foundSubFolder)
		{
			check = foundSubFolder;
		}
		else
			throw BadFolderNotFound();
	}
	Folder *foundLastLevel =  findSubFolder(fullPathtoFind[fullPathtoFind.size()-1],check->subFolders);

	if(foundLastLevel!=0){
		//print folder content
		check = foundLastLevel;

	}

	cout << "current Folder name is: "<< check->folderName<<endl;
	ostream_iterator<string> out(cout,"\n");
	cout << "Sub-Folders are:";
	for(int i=0;i<(int)check->subFolders.size();i++)
	{
		cout << "Folder["<<i<<"]"<<subFolders[i].getFolderName()<<endl;
	}

	cout << "\nFiles are:";
	for(int i=0;i<(int)check->files.size();i++)
	{
		cout << "File["<<i<<"]"<<files[i].getFileName()<<endl;
	}


}
void Folder::lproot()
{
	cout << "V/:\n";
	if(this->subFolders.size()==0)
	{
		cout << "\nFiles are:";
		for(int i=0;i<(int)this->files.size();i++)
		{
			cout << "File["<<i<<"]"<<files[i].getFileName()<<' '<< files[i].getRefCount()<<endl;
		}
	}
	else
	{
		lprootrec(this);
	}


}

void Folder::lprootrec(Folder *folder)
{
	if(folder->subFolders.size()==0)
		return;
	cout << "current Folder name is: "<< folder->folderName<<endl;
	ostream_iterator<string> out(cout,"\n");
	cout << "Sub-Folders are:";
	for(int i=0;i<(int)folder->subFolders.size();i++)
	{
		cout << "Folder["<<i<<"]"<<subFolders[i].getFolderName()<<endl;
	}

	cout << "\nFiles are:";
	for(int i=0;i<(int)folder->files.size();i++)
	{
		cout << "File["<<i<<"]"<<files[i].getFileName()<<' '<< files[i].getRefCount()<<endl;
	}

	for(unsigned int j=0; j < folder->subFolders.size();j++)
		lprootrec(&folder->subFolders[j]);
}




