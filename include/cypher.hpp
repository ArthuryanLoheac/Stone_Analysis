#pragma once
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <complex>
#include <unordered_map>

void cypher(const char *inputFile, const char *outputFile, const char *message);
void decypher(const char *inputFile);
std::string decryptMessage(const std::string &message);
std::string cryptMessage(const char *message);
