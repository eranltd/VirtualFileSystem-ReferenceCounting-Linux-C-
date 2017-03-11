/*
 * FileIO.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: eranpel
 */
#include "FileIO.h"

FileIO& FileIO::operator=(const FileIO& src) //operator=
{
	if(file == src.file)return *this;

	if(--file->refCount == 0)delete file;

	file = src.file;
	++file->refCount;

	return *this;

}

char FileIO::operator[] (fstream::pos_type i) const {
		if(file->file->fail())throw BadFile();
		//reading one char from file at i location
	file->file->seekg(i);
	return char(file->file->peek());
	}

	void FileIO::touch()const
	{
		//creates/changes the file time signature
		if(file->file->fail()){
			std::ofstream o(fileName.c_str());
		}
		else
		{
			utime(fileName.c_str(),0);
		}


	}

	void FileIO::copy(const string dst_file)
	{
		//run with iterators and copy the entire file byte after byte
		//copy function
		checkFile(); //checking condition
		ofstream out(dst_file.c_str());
		string tmp;
		while(!file->file->eof())
		{
			getline (*file->file,tmp);
			out << noskipws<<tmp<<'\n';
		}
		out.close();
		cout <<"Copying is done.\n";
	}

	void FileIO::remove()
	{
		//remove file from system
		 if( std::remove(fileName.c_str()) != 0 )
		 throw BadFile();
		 else
		cout <<"The file:"<<fileName<<" has been deletes successfully!"<<endl;
	}

	void FileIO::move(const string dst_file)
	{
		//copy the file from X location to Y and deletes from X location
		copy(dst_file);
		remove();
	}

	void FileIO::cat()
	{
		//prints the file content
		checkFile(); //checking condition
				istream_iterator<string> ifs(*file->file);
				istream_iterator<string> eof;
				ostream_iterator<string> ofs(cout," ");
				std::copy(ifs, eof, ofs);
				cout <<endl;
	}

	void FileIO::wc()
	{
		checkFile(); //checking condition
		char line[256];
		int linesCounter=0,wordsCounter=0,charsCounter=0;
		stringstream ss(stringstream::in | stringstream::out);
		while(file->file->getline(line,256-1))
				{
			ss<<line <<'\n';
			linesCounter++;
				}
		charsCounter = ss.str().length();
		istream_iterator<string>beg(ss),end;
		while(beg++!=end)wordsCounter++;
		cout << linesCounter << ' '<<wordsCounter << ' '<< charsCounter <<endl;
	}




