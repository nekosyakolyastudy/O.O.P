#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#define MAX_NUMBER_OF_ARGUMENT 5

using namespace std;
bool IsIdenticalString(const string &searchStr, const string &replaceStr);
string ReplaceString(string &strInFile, const string &searchStr, const string &replaceStr);
void CopyStrings(ifstream &input, ofstream &output, const string &searchStr, const string &replaceStr);

bool IsIdenticalString(const string &searchStr, const string &replaceStr)
{
	bool identicalStrings;
	(searchStr == replaceStr) ? identicalStrings = true : identicalStrings = false;
	return identicalStrings;
}

string ReplaceString(string &strInFile, const string &searchStr, const string &replaceStr)
{
	size_t positionOfMatchedString = strInFile.find(searchStr);
	while ((positionOfMatchedString != string::npos) && !IsIdenticalString(searchStr, replaceStr))
	{
		strInFile.replace(positionOfMatchedString, searchStr.length(), replaceStr);
		positionOfMatchedString = strInFile.find(searchStr, positionOfMatchedString + replaceStr.length());
	}
	return strInFile;
}

void CopyStrings(ifstream &input, ofstream &output, const string &searchStr, const string &replaceStr)
{
	string strInFile;
	while (getline(input, strInFile))
	{
		if (!strInFile.empty())
		{
			strInFile = ReplaceString(strInFile, searchStr, replaceStr);
			output << strInFile;
		}
		output << "\n";
	}
}

int main(int argc, char * argv[])
{
	if (argc != MAX_NUMBER_OF_ARGUMENT)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}

	ifstream input(argv[1]);

	if (!input.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	ofstream output(argv[2]);

	if (!output.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing\n";
		return 1;
	}

	string searchStr = argv[3], replaceStr = argv[4];

	if ((searchStr.empty()))
	{
		cout << "Empty line \n";
		return 1;
	}

	CopyStrings(input, output, searchStr, replaceStr);

	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}
	input.close();
	output.close();

	return 0;
}


