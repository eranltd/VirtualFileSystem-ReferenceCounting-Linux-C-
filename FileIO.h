/*
 * FIle.h
 *
 *  Created on: Mar 28, 2016
 *      Author: eranpel
 */

#ifndef FILEIO_H_
#define FILEIO_H_
/*This Object will 'wrap' a file system object*/
#include<fstream> //for fstream object
#include<iostream>
#include <utime.h> //for  utime, utimes - change file last access and modification times
#include<iterator>
#include<sstream>
#include<vector>
using namespace std;

struct BadFile : public exception
{
  const char * what () const throw ()
  {
    return "ERROR : the file does not exist in the computer";
  }
};

struct WrongIndex : public exception
{
  const char * what () const throw ()
  {
    return "ERROR : the position you have entered is wrong!(reached EndOfFile)";
  }
};

	class FileIO
	{
	private:
	struct FileValue {
		int refCount; //how much objects points to this object?
		bool shareable; //flag for determine if a change has made
		fstream *file;	//fstream object
		FileValue(string fileFromUser):refCount(1),shareable(true){
			file = new fstream(fileFromUser.c_str());
			} //c'tor
		~FileValue(){file->close();delete(file);}//d'tor
		};

	class CharOverload {
			public:
		CharOverload(fstream *file, fstream::pos_type pos) :
					file_(file), pos_(pos) {}
				CharOverload& operator=(char c) {
					file_->seekg(0,std::ios_base::end);
					fstream::pos_type end_pos = file_->tellg();
					if((int)pos_ > (int)(end_pos)+1)throw WrongIndex();//throw exception! if more than one char after eof
					file_->seekp(pos_);
					file_->put(c);
					return *this;
				}
				operator char() {
					file_->seekg(pos_);
					char result = file_->get();
					if( result == -1)throw WrongIndex();
					return char(result);
				}
			private:
				fstream* file_;
				fstream::pos_type pos_;
			};

	FileValue *file;	//private field to object that holds pointer to file on HD
	string fileName; //holds the fileName

	public:
	FileIO(string fileFromUser):fileName(fileFromUser){file =  new FileValue(fileName);} //c'tor
	FileIO(const FileIO& src):file(src.file),fileName(src.fileName){++file->refCount;} //copy c'tor
	FileIO& operator=(const FileIO&); //operator=
	string getFileName ()const{return fileName;}
	char operator[] (fstream::pos_type i) const;
	CharOverload operator[](fstream::pos_type i) { //writing one char to file at i location
		if(!file->file)throw BadFile();
		if(file->refCount >1 )
		{
			// the value is shared by other instances
			--file->refCount;
			file = new FileValue(fileName);
		}
		return CharOverload(file->file,i);
	}

	void touch()const;
	void copy(const string dst_file);
	void remove();
	void move(const string dst_file);
	void cat();
	void wc();
	void setFileName(string filename){fileName = filename;}
	void checkFile(){if(file->file->fail())throw BadFile();} //checking condition
	int getRefCount(){return file->refCount;}
	~FileIO(){if(--file->refCount==0) delete(file);} //d'tor


};

#endif /* FILEIO_H_ */
