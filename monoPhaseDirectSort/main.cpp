#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include "FileManager.h"
#include "monoPhaseDirectMerge.h"

#define N 10000 //count of elements to sort
#define INPUT "input.txt"
#define OUTPUT "input(sorted).txt"

using namespace std;
typedef unsigned long long ull;

/* Support functions*/
void generator(string filename, ull n)
{
	srand(time(NULL));
	ofstream file;
	file.open(filename);
	for (ull i = 0; i < n; i++)
	{
		file << " " << rand();
	}
	file.close();
}

void show_file(string filename)
{
	ifstream file;
	file.open(filename);
	int temp;
	while (!file.eof())
	{
		file >> temp;
		cout << temp << " ";
	}
	cout << endl;
}

void check(string filename)
{
	bool flag = 1;
	ull counter = 1;
	ull tmp1, tmp2;
	ifstream f;
	f.open(filename);
	f >> tmp1;
	while (!f.eof())
	{
		f >> tmp2;
		counter++;
		if (tmp1 > tmp2)
		{
			cout << "Error pos: " << counter << "  |  " << tmp1 << " > " << tmp2 << endl;

			flag = 0;
		}
		tmp1 = tmp2;
	}
	if (flag)
	{
		cout << "Sorting status: ok" << endl;
	}
	cout << counter << " elements was sorted" << endl;
}

void len(string filename)
{
	ull counter = 0;
	ifstream f;
	f.open(filename);
	ull tmp;
	while (!f.eof())
	{
		f >> tmp;
		counter++;
	}
	cout << counter << " elements to sort" << endl;
}



int main()
{
	generator(INPUT, N);
	monoPhaseDirectMerge(INPUT);
	check(OUTPUT);
}