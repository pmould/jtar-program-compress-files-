#include "file.h"
#include <cstring>
using namespace std;

File::File()
{
    //   strcpy (UPC, "\0");  strcpy (Artist, "\0");
     //  strcpy (Title, "\0");
       strcpy (name,"\0");  strcpy (pmode, "\0");
       strcpy (size, "\0"); strcpy (stamp, "\0");
       isDir = false;
}

File::File (char Name[81], char Pmode[5], char Size[7], char Stamp[16], bool IsDir)
{
       strcpy (name,Name);  strcpy (pmode, Pmode);
       strcpy (size, Size); strcpy (stamp, Stamp);
       isDir = IsDir;
} 

File & File::operator = (const File& otherFile)
{
       strcpy (name, otherFile.name);  strcpy (pmode, otherFile.pmode);
       strcpy (size, otherFile.size); strcpy (stamp, otherFile.stamp);
       isDir = otherFile.isDir;
	return *this;
}

File::File( const File& otherFile)
{
       strcpy (name, otherFile.name);  strcpy (pmode, otherFile.pmode);
       strcpy (size, otherFile.size); strcpy (stamp, otherFile.stamp);
       isDir = otherFile.isDir;
}


string File::getName()
{
	return name;
}

string File::getPmode()
{
	return pmode;
}

string File::getSize()
{
	return size;
}

string File::getStamp()
{
	return stamp;
}

bool File::getIsDir()
{
        return isDir;
}

void File:: setDir(bool value)
{
	isDir = value;	
}
/*
istream & operator >> (istream & stream, File & C)
{
       stream.getline(C.UPC,13, '\n');
       if (strlen(C.UPC) == 0)  return stream;
       stream.getline(C.Artist, 24, '\n');
       stream.getline(C.Title, 36, '\n');
       return stream;
}

ostream & operator << (ostream & stream, File & C)
{
        stream << C.UPC << "|" << C.Artist << "|" <<C.Title << "|";
	return stream;
}
*/
