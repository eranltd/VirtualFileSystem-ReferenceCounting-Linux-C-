# VirtualFileSystem-ReferenceCounting-Linux-CPP
implementation of linux-like FileSystem using CPP

This project is about upgraded file system implementation, the file objects contains support in reference counting
In this project is about an object oriented world of FileSystem on a virtual drive on heap using folder hierarchy
The file object is "wrapping" the  fstream::std and is data will be on the "heap"

this project contain 3 parts:

1.file object
2.folder object
3.Mini-terminal for executing commands


compile using g++ FS.cpp FileIO.cpp Folder.cpp ParsedInput.h Terminal.cpp -o myVFS

Terminal Functionality : 

[1] read FILENAME POSITION
[2] write FILENAME POSITION CHARACTER
[3] touch FILENAME
[4] copy SOURCE_FILENAME TARGET_FILENAME
[5] remove FILENAME
[6] move SOURCE_FILENAME TARGET_FILENAME
[7] cat FILENAME
[8] wc FILENAME
[9] ln TARGET_FILENAME LINK_NAME
[10] mkdir FOLDERNAME
[11] chdir FOLDERNAME
[12] rmdir FOLDERNAME
[13] ls FOLDERNAME
[14] lproot
[15] pwd
[16] exit

executing example:

[terminal] $ ./myVFS
[input] pwd
[output] V/
[input] touch V/test.txt
[input] write V/test.txt 0 d
[input] read V/test.txt 0
[output] d
[input] write V/test.txt 1 e
[input] write V/test.txt 2 J
[input] write V/test.txt 3 o
[input] write V/test.txt 4 n
[input] write V/test.txt 5 g
[input] cat V/text.txt
[output] ERROR: no such filename
[input] cat V/test.txt
[output] deJong
[input] mkdir V/tmp/
[input] chdir V/tmp/
[input] pwd
[output] V/tmp/
[input] ls V/tmp/
[output] V/tmp/:
[input] copy V/test.txt V/tmp/t.dat
[input] copy FS.cpp V/tmp/f.cc
[input] ln V/tmp/f.cc V/tmp/FS.cpp
[input] lproot
[output] V/:
[output] test.txt 1
[output] V/tmp/:
[output] f.cc 2
[output] t.dat 1
[output] FS.cpp 1
[input] rmdir V/tmp/
[input] lproot
[output] V/:
[output] test.txt 1
[input] exit
[terminal] $


