#include "FileManager.h"


FileManager::FileManager(int _inCount, int _outCount) :inCount(_inCount), outCount(_outCount)
{
	input.reserve(inCount);
	output.reserve(outCount);
	for (int i = 0; i < inCount; i++)
	{
		std::string name = "__tmp0_" + std::to_string(i) + ".txt";
		input.push_back(std::pair <std::fstream, std::string>(std::fstream(name, std::ios::out), name));
	}
	for (int i = 0; i < outCount; i++)
	{
		std::string name = "__tmp1_" + std::to_string(i) + ".txt";
		output.push_back(std::pair <std::fstream, std::string>(std::fstream(name, std::ios::out), name));
	}
}

FileManager::~FileManager()
{
	for (int i = 0; i < inCount; i++)
	{
		input[i].first.close();
		remove(input[i].second.c_str());
	}
	for (int i = 0; i < outCount; i++)
	{
		output[i].first.close();
		remove(output[i].second.c_str());
	}
}

void FileManager::swap()
{
	for (int i = 0; i < inCount; i++)
	{
		input[i].first.close();
		input[i].first.open(input[i].second, std::ios::out);
	}
	for (int i = 0; i < outCount; i++)
	{
		output[i].first.close();
		output[i].first.open(output[i].second, std::ios::in);
	}
	input.swap(output);
}

void FileManager::swap(int inIndex, int outIndex)
{
	input[inIndex].first.close();
	input[inIndex].first.open(input[inIndex].second, std::ios::out);
	output[outIndex].first.close();
	output[outIndex].first.open(output[outIndex].second, std::ios::in);
	input[inIndex].swap(output[outIndex]);
}

int FileManager::read(int index)
{
	int tmp;
	input[index].first >> tmp;
	return tmp;

	//int a;
	//input[index].first.read((char *)&a, sizeof(int));
	//return a;
}

void FileManager::write(int index, int value)
{
	output[index].first << " " << value;
	//output[index].first.write((char *)&value, sizeof(value));
}

bool FileManager::eof(int index)
{
	return input[index].first.eof();
}


int FileManager::getInCount()
{
	return inCount;
}

int FileManager::getOutCount()
{
	return outCount;
}