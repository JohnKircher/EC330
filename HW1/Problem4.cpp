#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]){

	string line;
	string longestLine = "";
	string fileName;
	fileName = argv[1];
	ifstream myFile (fileName);
	if(myFile.is_open())
	{
		while(getline(myFile,line))
		{
			if(line.length() > longestLine.length())
			{
				longestLine = line;
			}
		}
		cout << longestLine;
		cout << "\n";
		myFile.close();

	}
	return 0;
}

