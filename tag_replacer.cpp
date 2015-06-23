// Note: Still in progress
// Grammar tag changer
// Author: JHutter
//
// Program:
// This program reads in tagged (and fixtagged) files and replaces legacy tags (past participle adverbials)
// with the new tag (xvbn).

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void getFileNames(ifstream& inFile, string& oldFileName, string& fileGroup, int& fileNumStart, int& fileNumEnd);
string getNewFileName(ifStream& inFile, string oldFileName, string& newFileName);


int main()
{
	ifstream 	inFile;
	ofstream 	outFile;
	string 		word,
				tag;
	char		peekChar;
	string		oldFileName,
				filePath,
				fileGroup = "";
	int			fileNumStart = 0,
				fileNumEnd = 0,
				fileNumTemp = 0;

    cout << "Welcome to the tag replacer.\n";

    getFileNames(inFile, oldFileName, fileGroup, fileNumStart, fileNumEnd); //Get the range of files to read from


    //getNewFileName(inFile, oldFileName, newFileName)



	return 0;
}

void getFileNames(ifstream& inFile, ofstream& outFile, string& oldFileName, string& fileGroup, int& fileNumStart, int& fileNumEnd)
{
    int fileNumTemp = 0;
	cout << "\nEnter the file group (e.g., prec or srep):\n";
	cin >> fileGroup;
	cout << "You entered " << fileGroup << " for the file group.\n";

	cout << "Enter the file number start for the file group (e.g., 000):\n";
	cin >> fileNumStart;
	cout << "You entered " << fileNumStart << " for the file number start.\n";

	cout << "Enter the file number end for the file group (e.g., 060):\n";
	cin >> fileNumEnd;
	cout << "You entered " << fileNumEnd << " for the file number end.\n";

    cout << endl << endl << fileGroup << fileNumStart << " is the first file.\n";
    cout << fileGroup << fileNumEnd << " is the last file.";

    inFile.open("fileNamesHere.txt");
    for (fileNumTemp = fileNumStart; fileNumTemp >= fileNumEnd; fileNumTemp++)
        outFile << fileGroup << fileNumTemp << ".txt";
    inFile.close();
	return;
}

string getNewFileName(string oldFileName, string& newFileName)
{
	string fileNamePrefix = "mod",
	newFileName = fileNamePrefix + oldFileName;
	return newFileName;
}
//
//void readFile()
//
//void readFile()
//
//void replaceOldTag()
//
