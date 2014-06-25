#include <iostream>
#include <string>
#include<stdio.h>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <sys/stat.h>
#include <stdlib.h> 
#include <list>
#include "file.h"
using namespace std;



//This fiunction check whether a file is a directory or a file and returns true if it is a file or false if it is a file
bool isDirectory( string file)
{
        FILE *in;
        char buff[512];
        string statCom = "stat ";
        statCom += file;
        statCom += " | grep 'Size'";
        if(!(in = popen(statCom.c_str(), "r")))
        return 1;
           while(fgets(buff, sizeof(buff), in)!=NULL){}
        string temp = buff;

        if (temp.find("file") != -1)
        {
                return false;
        }
        if ( temp.find("directory") != -1)
        {
                return true;
        }

}

// This funchtion is used to check for errors in the command line arguements and output error messages where appropriate
// Also this function includes the --help operation for the jtar command
void parseCmdLineFlags(int argc, char ** argv)
{
        if ( argc ==1)
        {
                cout << "Invalid input on the command line. Refer to --help" << endl;
                exit(0);
        }

        string op = argv[1];            // Operation of tar file
        // Vailidate command line input should have a second arguemetn equal to a valid operation
         if ( op != "-cf" && op != "-tf" && op != "-xf" && op != "--help")
        {
                cout << "Invalid operation. Refer to --help." << endl;
                exit(0);
        }
        if (argc == 2)
        {
                if (op == "--help")
                {
                        cout << "jtar command:\n\n";

                        cout << setw(40) << left << "jtar - cf tarfile file1 dir1 ..."
                             << "Specifies jatar to make a tar file named tarfile based on the files or directories following the name of the tarfile.\n";
                        cout << setw(40) << left <<  "jtar - tf tarfile"
                             <<  "This specifies jtar to list the names of all files that have packed into a tar file. It does not recreate anything.\n";
                        cout << setw(40) << left <<  "jtar - xf tarfile"
                             << "This specifies jtar to read a tar file, and recreate al lthe files saved in that tarfile.\n" << endl;
                }
                else
                        cout << "1. Invalid operation. Refer to --help." << endl;
                exit(0);
        }

        string tarName = argv[2];               // name of tar file
//      // If the operation is cf make a tar file based on the files and directories listed in the command line
        if ( op == "-cf")
        {
        // MAKE A TAR FILE
        //                 // Validate that if the -cf option is selected that the argc is at least 4 
                        if (argc < 4)
                {
                        cout << "3. Invalid format. Refer to --help." << endl;
                        exit(0);
                }

        }
        if ( op == "-tf" || op == "-xf")
        {
                fstream readTarFile;
                readTarFile.open(argv[2], ios::in | ios:: out | ios:: binary);

             if (argc > 3)
                {
                        cout << "4. Invalid format. Refer to --help." << endl;
                        exit(0);
                }
                if( !readTarFile )
                {
                        cout << "5. The tar file specified does not exist." << endl;
                        exit(0);
		}
	}

        for (int i = 3; i <argc ; i++)
         {
        	fstream tempFile;
               tempFile.open(argv[i]);
          	
		if ( isDirectory(argv[i]) == false)
		{
                	if (!tempFile)
                	{
                	          cout << "The File or directory, " <<argv[i] << " does not exist" << endl;
                        	   exit(0);
               		 }
         	 }

	}
}

// This function returns the size of the file parameter using stat command in linux
string getSizeStat( string file)
{	
	string sizeF;
        fstream statFile;
        statFile.open("statFile", ios::in | ios::out | ios::trunc);
	string statCom = "stat ";
        statCom += file;
        statCom += " | grep 'Size' | cut -c 9-15 ";
        statCom += ">> statFile";
        system(statCom.c_str());
        statFile.seekg(0, ios::beg);
        statFile >> sizeF;
        statFile.close();
	system( "rm statFile");	
	return sizeF;

}


// This function returns the Protection mode of the file parameter using stat command in linux
string getPmodeStat( string file)
{
        string sizeF;
        fstream statFile;
        statFile.open("statFile", ios::in | ios::out | ios::trunc);
        string statCom = "stat ";
        statCom += file;
        statCom += " | grep 'Access' | cut -c 10-13 ";
        statCom += ">> statFile";
        system(statCom.c_str());
        statFile.seekg(0, ios::beg);
        statFile >> sizeF;
        statFile.close();
	system( "rm statFile");	
        return sizeF;

}


// This function returns the Time Stamp of the file parameter using stat command in linux
string getStampStat(string file)
{
        string sizeF;
        fstream statFile;
        statFile.open("statFile", ios::in | ios::out | ios::trunc);
        string statCom = "stat ";
        statCom += file;
	statCom += "| grep 'Access' | sed 's/://g' | sed 's/ //g' | sed 's/-//g' | tail -n 1 | cut -c 7-20";
        statCom += ">> statFile";
        system(statCom.c_str());
        statFile.seekg(0, ios::beg);
        statFile >> sizeF;
	sizeF.insert(12,".");
        statFile.close();
	system( "rm statFile");	
        return sizeF;

}
// This function prints the name of the file to stdout
void printName(string s)
{
	cout << s << endl;
	
}

// This function is used to obtain all the files and directories to be placed into the tar file and store them into the list that is a pass-by reference parameter.
void listAll(string s, list<string> &myList)
{


	bool val = false;
	printName(s);
	myList.push_back(s);
	if ( isDirectory(s) )
	{
		string c;
	        fstream statFile;
	        statFile.open("statFile", ios::in | ios::out | ios::trunc);
	        string statCom = "ls ";
	        statCom += s;
	        statCom += ">> statFile";
	        system(statCom.c_str());
		statFile.clear();
 
		statFile.close();
	        statFile.open("statFile", ios::in);
	       statFile.seekg(0, ios::beg);

		char cS[81];

	        while(statFile && val ==false)
		{

	    	statFile >> c;
		statFile.ignore();  
	   
		statFile.ignore(); 
		if(statFile.eof())
			val = true; 
		statFile.unget();
		 
			listAll(s + "/" + c, myList);
		}
     			 statFile.close();
		//	system( "rm statFile");	
	}
}


// This is the main function that runs the jtar program which is a parsed-down version of the linux utility jtar that will create a tar file, unpack a tar file, and list the files packed into a tar file
int main(int argc, char ** argv)
{
    
     parseCmdLineFlags(argc,argv);  // Check for errors in the command line arguements 
     list<string> fileNameList;    // List to store list of all file names and directoies to be placed into the tar file
     int tarFileSize = 0;	   // Size of tar file
     string tarName = argv[2];     // Name of the tar file
	
     // If the -xf operation is chosen this specifies the program to read a tar file, and recreate all the files saved in that tarfile including making any necessary directories
     if ((string) argv[1] == "-xf") 
     {
	int p= 0;
	int textSize;
        File fileRead;
        string tarN = argv[2];		// Name of the tar file
        fstream tarStream( tarN.c_str(),ios::in);   //Opens the tarfile

        int tarZ;
        tarStream >> tarZ;  		// get the size of the tar file from the beginning of the tar file
        tarStream.ignore();            // move to the next position in the tarfile
      
	// Reads the entire tar file from the beginning till the end reading in all the File objects to a a File object
	// If the File Object is a directory it creates the new directory 
	// If the file Object is a file it creates the file
	while (!tarStream.eof())	
        {
                tarStream.unget();  // Go backward by 1 in the file
                tarStream.read((char *) &fileRead, sizeof(File));  // Read a File Object from the tar file and store it in a File variable
                if ( fileRead.getIsDir()== true)	// If the File Object read in is a directory then create a new directory
		{	string statCom ="mkdir ";
			statCom += fileRead.getName();
			system(statCom.c_str());	// system call to create a direcory of the File Object
		}
		else// If it is a file then create the file 
		{
//			cout << "fileRead Name: " << fileRead.getName() << endl;
        		fstream newFile; // This is the stream of the new file that is created
			newFile.open((fileRead.getName()).c_str(),ios::out); //Create the local file of the File Object read in from the tar file

			char ch;
			// Puts the text contents of the file Object into the local file that was created
			// Reads each character of the text content of the file and places into in the newly created local file
			for(int i = 0; i <atoi((fileRead.getSize()).c_str()); i++)
			{
				tarStream.get(ch); // Get a character from the tar file
				newFile.put(ch); // Put a character into the newly created local file
			}
		}
			// Set the Protection mode of the created file to the original protection mode
			string statCom ="chmod ";
			statCom += fileRead.getPmode();
			statCom +=" ";
			statCom += fileRead.getName();
//			cout << statCom << endl;
			system(statCom.c_str());	// system call to set the Protection Mode of a direcory of the File Object

			// Set the time Stamp mode of the created file to the original time stamp
			statCom ="touch -t ";
			statCom += fileRead.getStamp();
			statCom +=" ";
			statCom += fileRead.getName();
//			cout << statCom << endl;
			system(statCom.c_str());	// system call to set  the time Stamp of a direcory of the File Object
                tarStream.ignore(); // move forward by 1 in the tarfile
	}

      }

     else // If the -tf operation is chosen a list of the names of all the files that have been packed into the tarfile specified will be displayed
     if ( (string) argv[1] == "-tf")
     {
	int TextSize;
	File fileRead;
     	string tarN = argv[2];  // Tar Name variable
	fstream tarStream( tarN.c_str(),ios::in);
	int tarZ;      // Tar Size variable
	tarStream >> tarZ;  //Read in the tar file siz from the beginning of the tar file
	tarStream.ignore();
	// Reads the entire tar file from the beginning till the end reading in all the File objects to a a file 
	while (!tarStream.eof())
	{
		tarStream.unget();
                tarStream.read((char *) &fileRead, sizeof(File)); // Read in File Object
		cout << fileRead.getName() << endl; // Prints out the name of the file to the screen
		// If the file Object read in from the tarfile is a file then skip through the text content of the file 
		if ( fileRead.getIsDir()== false)
			tarStream.seekg(atoi((fileRead.getSize()).c_str()), ios::cur); // skips through bytes (equal to the size of the file) in the tarfile
		tarStream.ignore();
	}


     }
     else
     if ( (string) argv[1] == "-cf")
     {
     // If the cf operation is selected then it would create a tarfile with the name specified based on the file or directories following the name of the tarfile in the command line arguemtnts
	// Output the name of the tarFile to be created
	cout << "Output of files and directories in the jtar file - " << tarName << ":" << endl;
	for ( int i=3; i< argc; i++)
	{
	listAll( (string) argv[i], fileNameList); // Add the the file to the fileName list and if it is a directory add all the files names of the files in that directory
	string itString;
	list<File> fileList;   // List of all the File Objects to be added to the tar file
	char  itStr[81];	// File Name char * variable
	char  p[5];		// Protection Mode char * variable
	char  s[7];		// Size  char * variable
	char  st[16];		// Time Stamp char * variable 
	
	char * itChar;
	// Iterate through the list of file Names to be added to the file and create the File Object of the file and put it into the list of all File Objects to be added to the tar file
	for (list<string>::iterator iter = fileNameList.begin(); iter != fileNameList.end(); iter++)
	{

	
		// The follwing code converts the string variables of the File Object attributes to a char * variable that can be used as parameters to the explicit constructor of the  File Object
		itString = *iter;
		string sizeF, stampF;
		string pModeF;
		sizeF = getSizeStat(*iter);
		stampF = getStampStat(*iter);
		pModeF = getPmodeStat(*iter);

		int TempNumOne = itString.size();
		int TempNum2 = pModeF.size();
		int TempNum3 = sizeF.size();
		int TempNum4 = stampF.size();
		
		// Puts file Name string variable into a char * variable
		for (int a=0;a<=TempNumOne;a++)
       		 {
        	    itStr[a]=itString[a];
       		 }
		// Puts the protection mode string variable into a char * variable
		for (int a=0;a<=TempNum2;a++)
       		 {
        	    p[a]=pModeF[a];
       		 }
		// Puts file Size  string variable into a char * variable
		for (int a=0;a<=TempNum3;a++)
       		 {
        	    s[a]=sizeF[a];
       		 }
		// Puts the time stamp string variable into a char * variable

		for (int a=0;a<=TempNum4;a++)
       		 {
        	    st[a]=stampF[a];
       		 }



	tarFileSize += atoi(s);
	
		File tempFile(itStr, p, s,st, false); // Constructs a File Object of the File that is read in from the list using  call to the explicit constructor
		//If the file Object read in is a directory set it as one
		if ( isDirectory(*iter) == true)
		{
			tempFile.setDir(true);  // Set File Object as a Directory
		}
		fileList.push_back(tempFile);	// Add File Object variable to the list of all the File Objects
	}

	// The following code creates the tar file from the list of all the File Objects
	
	fstream newTarFile( tarName.c_str(), ios::out | ios::binary ); // Create a tarFile with the name specified in the command line arguement
	newTarFile << tarFileSize;	// Write out the tarfile size to the tarfile

	//Mount files to tarFile
	// Iterate throught the list of File objects, and construct a local File object for each item in the list
	for (list<File>::iterator iter = fileList.begin(); iter != fileList.end(); iter++)
	{
		newTarFile.write((char *) &(*iter), sizeof(File));	// Write out the File Object to the tarfile
		// If the File Object is a text file then output the text contents of the text file following the File Object
		if ((*iter).getIsDir() == false)
		{
		       string temp;
    			FILE *in;
   			char buff[10000];
   	      	        string statCom = "cat ";
		        statCom += (*iter).getName();
		    	if(!(in = popen(statCom.c_str(), "r"))) // Using the cat command to read in the file's text contents to a FILE variable
       				 return 1;
			//Adds  each line of the FILE object's text contents to a char * variable and then store the char * variable into a string variable
			//Using fgets to read in  a line in the FILE stream to a char array
		        while(fgets(buff, sizeof(buff), in)!=NULL){
		        	temp += buff; 	// Append each line of the text contents to a string variable that would hold all the text contents of a file
			}
        		newTarFile << temp;	// Write the text Contents of the File that is read from the lisr to the Tar File
		}	
	}		

      }
	
	
	return 0; // Terminates the program
}
}

