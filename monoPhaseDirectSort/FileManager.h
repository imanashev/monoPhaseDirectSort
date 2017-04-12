#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


class FileManager
{
	std::vector <std::pair <std::fstream, std::string>> input, output;
	int inCount, outCount;
public:
	FileManager(int inCount, int outCount);
	~FileManager();
	void swap();
	void swap(int inIndex, int outIndex);
	int read(int index);
	void write(int index, int value);
	bool eof(int index);
	int getInCount();
	int getOutCount();

};