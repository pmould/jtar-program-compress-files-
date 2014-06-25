
#include <cstring>
#include <string>
#include <fstream>
using namespace std;

class File
{
   public :
       File (const File& otherFile);
      // File (char Name [81] , char Pmode [5],char Size[7], char Stamp [16]);
       File (char Name [81] , char Pmode [5],char Size[7], char Stamp [16], bool IsDir);
       File ();
       File & operator = (const File& otherFile);
     //  friend istream & operator >> (istream & stream, CD & C);
     //  friend ostream & operator << (ostream & stream, CD & C);
     //  int Pack (IOBuffer & Buffer) const;
     //  int Unpack (IOBuffer & Buffer);
       string getName();
       string getPmode();
       string getSize();
       string getStamp();
       bool getIsDir();
       void setDir(bool value); // Set a file to a directory
      // int recordSize();

   private :
  //     String UPC, Artist, Title;
  	char name [81], pmode[5], size[7], stamp[16];
	bool isDir;
};
