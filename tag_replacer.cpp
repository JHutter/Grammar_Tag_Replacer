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
#include <cstdlib>
using namespace std;

void createNewDirectory();
void getFileNames(string& fileGroup, int& fileNumStart, int& fileNumEnd, string& fileSuffix);
void getTags(string& oldTag1, string& oldTag2, string& newTag);
void getHeader(ifstream& inFile, ofstream& outFile, string oldTag1, string oldTag2, string newTag);
string replaceOldTag(string currentTag, string oldTag1, string oldTag2, string newTag);
void readTaggedLine(istream& inFile, ofstream& outFile, string oldTag1, string oldTag2, string newTag);
int findDigitLength(int inputNumber);
string findZeroes(int length);

int main()
{
	ifstream 	inFile,
                listInFile;
	ofstream 	outFile,
                listOutFile;
	string 		word,
				tag;
	char		peekChar;
	string		fileName,
				filePath,
				fileGroup = "",
				fileSuffix = "",
				newFilePath = "";
	int			fileNumStart = 0,
				fileNumEnd = 0;
    string      oldTag1 = "",
                oldTag2 = "",
                newTag = "";

    cout << "Welcome to the tag replacer.\n";
    createNewDirectory(); ///home/jhutter/Documents/CE WR Coding/new");
    getFileNames(fileGroup, fileNumStart, fileNumEnd, fileSuffix); //Get the range of files to read from
    getTags(oldTag1, oldTag2, newTag); //Get the tags to be replaced and to replace with

    listInFile.open("files_changed.txt");
    listOutFile.open("files_changed.txt");
    while (listInFile.peek() != EOF)
    {
        listInFile >> fileName;
        inFile.open(fileName.c_str());

        newFilePath = "tags_replaced/" + fileName;
        outFile.open(newFilePath.c_str());

        getHeader(inFile, outFile, oldTag1, oldTag2, newTag);
        readTaggedLine(inFile, outFile, oldTag1, oldTag2, newTag);
    }

    cout << "Tag replacing complete. Please check files_changed.txt for a list of files changed\n"
        << "and tags_replaced for the files changed.";
	return 0;
} //End of main

//functions
void createNewDirectory() //New directory to dump new files into, also makes list of files to replace tags in
{
    const int dir_err = system("mkdir -p tags_replaced");
    if (-1 == dir_err)
    {
        printf("Error creating directory!n");
        exit(1);
    }
    return;
}
void getFileNames(string& fileGroup, int& fileNumStart, int& fileNumEnd, string& fileSuffix)
{
    ofstream outFile;
    outFile.open("files_changed.txt");
    int     firstLength,
            secondLength;
    string  firstZeroes,
            secondZeroes;

	cout << "\nEnter the file group (e.g., prec or srep):\n";
	cin >> fileGroup;

	cout << "Enter the file number start for the file group (e.g., 000):\n";
	cin >> fileNumStart;

	cout << "Enter the file number end for the file group (e.g., 060):\n";
	cin >> fileNumEnd;

	cout << "Enter the suffix for the file group (e.g. zz or az):\n";
	cin >> fileSuffix;

    firstLength = findDigitLength(fileNumStart);
    secondLength = findDigitLength(fileNumEnd);
    firstZeroes = findZeroes(firstLength);
    secondZeroes = findZeroes(secondLength);

    cout << endl << endl << fileGroup << firstZeroes << fileNumStart << fileSuffix << ".txt is the first file.\n";
    cout << fileGroup << secondZeroes << fileNumEnd << fileSuffix << ".txt is the last file.\n";

    for (int tempNum = fileNumStart; tempNum <= fileNumEnd; tempNum++)
    {
        int tempLength = findDigitLength(tempNum);
        string tempZeroes = findZeroes(tempLength);
        cout << fileGroup << tempZeroes << tempNum << fileSuffix << ".txt\n";
        outFile << "hey";
        //listInFile << fileGroup << tempZeroes << tempNum << fileSuffix << ".txt\n";
    }

	return;
}

void getTags(string& oldTag1, string& oldTag2, string& newTag)
{
    cout << "Please enter the first old tag to be replaced (such as ^vbd+nf+++xvbnx+=):\n";
    cin >> oldTag1;
    cout << "Please enter the second old tag to be replaced (^vbd+nf+++xvbn+=):\n";
    cin >> oldTag2;
    cout << "Please enter the new tag:\n";
    cin >> newTag;

    return;
}


void getHeader(ifstream& inFile, ofstream& outFile, string oldTag1, string oldTag2, string newTag)
{
    string  currentDate,
            username,
            headerLine = "";

    cout << "Please enter the current date in mm/dd/yyyy format:\n";
    cin >> currentDate;
    cout << "Please enter your name or initials:\n";
    getline(cin, username);

    outFile << "<Tags replaced on " << currentDate << " by " << username
        << ", old tags: " << oldTag1 << " and " << oldTag1
        << "new tag: " << newTag << ">";

    do
    {
        getline(inFile, headerLine);
        outFile << headerLine;
    }
    while (headerLine != "<end of header>");

    return;
}

string replaceOldTag(string currentTag, string oldTag1, string oldTag2, string newTag)
{
    if (currentTag == oldTag1 || currentTag == oldTag2) //There are two versions of tag to replace
        return newTag;
    else
        return currentTag;
}

void readTaggedLine(istream& inFile, ofstream& outFile, string oldTag1, string oldTag2, string newTag)
{
    string  word,
            tag;

    while (cin.peek() != EOF)
    {
        inFile >> word;
        outFile << word;

        inFile >> tag;
        outFile << replaceOldTag(tag, oldTag1, oldTag2, newTag);

        word = "";
        tag = ""; // clear the variables to avoid repeated line at end of file
    }
    return;
}

int findDigitLength(int inputNumber)
{
    int digitLength;
    if (inputNumber < 10 && inputNumber > -10)
        return 1;
    else
    {
        do
        {
            inputNumber /= 10;
            digitLength++;
        }
        while (abs(inputNumber) > 0);
        return digitLength;
    }
}

string findZeroes(int length)
{
    if (length == 1)
        return "00";
    if (length == 2)
        return "0";
    return "";
}
