#include "monoPhaseDirectMerge.h"

//Естественное слияние
/*
void firstdistrib(fstream& file, FileManager&  manager)
{
bool flag = 0;
int prev, next;
file >> next;
manager.write(flag, next);
while (!file.eof())
{
prev = next;
file >> next;
if (prev <= next)
{
manager.write(flag, next);
}
else
{
flag = !flag;
manager.write(flag, next);
}
}
}
*/

//Прямое слияние
void firstDistrib(std::fstream& file, FileManager&  manager)
{
	bool flag = 0;
	int tmp;
	while (!file.eof())
	{
		file >> tmp;
		manager.write(flag, tmp);
		flag = !flag;
	}
}

bool merge(FileManager& manager)
{
	ull pos0, pos1;		//position in series
	int elem0, elem1;	//elements in series
	bool flag = 0;		//number of out file
	ull length = 1;		//series lenght
	ull count = 10;		//series count

	while (count > 1)
	{
		count = 0;
		while (!manager.eof(0) && !manager.eof(1))
		{
			pos0 = 0;
			pos1 = 0;
			if (manager.eof(0))
			{
				pos0 = length;
				break;
			}
			else
			{
				elem0 = manager.read(0);
			}
			if (manager.eof(1))
			{
				pos1 = length;
				break;
			}
			else
			{
				elem1 = manager.read(1);
			}
			while ((pos0 < length) && (pos1 < length))
			{
				if (elem0 < elem1)
				{
					manager.write(flag, elem0);
					pos0++;
					if (manager.eof(0))
					{
						pos0 = length;
					}
					if (pos0 < length)
					{
						elem0 = manager.read(0);
					}
				}
				else
				{
					manager.write(flag, elem1);
					pos1++;
					if (manager.eof(1))
					{
						pos1 = length;
					}
					if (pos1 < length)
					{
						elem1 = manager.read(1);
					}
				}
			}

			while (pos0 < length)
			{
				manager.write(flag, elem0);
				pos0++;
				if (manager.eof(0))
				{
					pos0 = length;
				}
				if (pos0 < length)
				{
					elem0 = manager.read(0);
				}
			}
			while (pos1 < length)
			{
				manager.write(flag, elem1);
				pos1++;
				if (manager.eof(1))
				{
					pos1 = length;
				}
				if (pos1 < length)
				{
					elem1 = manager.read(1);
				}
			}
			flag = !flag;
			count++;
		}
		if (!manager.eof(0) || !manager.eof(1))
		{
			count++;
		}
		while (!manager.eof(0))
		{
			elem0 = manager.read(0);
			manager.write(flag, elem0);
		}
		while (!manager.eof(1))
		{
			elem1 = manager.read(1);
			manager.write(flag, elem1);
		}
		length *= 2;
		manager.swap();
	}
	return flag;
}

void monoPhaseDirectMerge(std::string filename)
{
	FileManager manager(2, 2);
	bool flag;	//number of result file
	std::fstream file;
	std::fstream result;
	file.open(filename, std::ios::in);
	result.open(filename.insert(filename.length() - 4, "(sorted)"), std::ios::out); //create result file

	/*Sort*/
	firstDistrib(file, manager);
	manager.swap();
	flag = merge(manager);

	/*Copy to result file*/
	while (!manager.eof(!flag))
	{
		result << " " << manager.read(!flag);
	}

	file.close();
	result.close();
}