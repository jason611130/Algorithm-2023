#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;
int main(int argc, char** argv)
{
	int nets;
    // if(argc != 3)
    // {
    //     cout << "Usage: ./[exe] [input file] [output file]" << endl;
    //     exit(1);
    // }
    // // open the input file
    // fstream fin;
    // fin.open(argv[1], fstream::in);
    // if(!fin.is_open())
    // {
    //     cout << "Error: the input file is not opened!!" << endl;
    //     exit(1);
    // }
    fstream fin;
    fin.open("10x10.in");
    char buffer[100];

    fin >> buffer;
    string s = buffer;

	if (s == "grid") {
		fin >> buffer;
		int row = atoi(buffer);

		fin >> buffer;
		int column = atoi(buffer);
    }

	fin >> buffer;
	s = buffer;

	if (s == "capacity") {
		fin >> buffer;
		int capacity = atoi(buffer);
	}

	fin >> buffer;
	s = buffer;
	fin >> buffer;
	s = buffer;

	if (s == "net") {
		fin >> buffer;
		nets = atoi(buffer);
	}

	for (int i = 0; i < nets; ++i) {
		fin >> buffer;
		int netID = atoi(buffer);
		fin >> buffer;
		int sx = atoi(buffer);
		fin >> buffer;
		int sy = atoi(buffer);
		fin >> buffer;
		int tx = atoi(buffer);
		fin >> buffer;
		int ty = atoi(buffer);
	}
	return 0;
}