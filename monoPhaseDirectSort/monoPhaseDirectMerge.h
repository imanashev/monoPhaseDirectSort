#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "FileManager.h"
typedef unsigned long long ull;

// Однофазная сортировка прямым слиянием
void monoPhaseDirectMerge(std::string filename);
void firstDistrib(std::fstream& file, FileManager&  manager);
bool merge(FileManager& manager);
