#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "FileManager.h"
typedef unsigned long long ull;

// ���������� ���������� ������ ��������
void monoPhaseDirectMerge(std::string filename);
void firstDistrib(std::fstream& file, FileManager&  manager);
bool merge(FileManager& manager);
