#pragma once
#include<iostream>
#include<vector>
using namespace std;

string hexStr(unsigned char* data, int len);
void strToCharArray(string str, char* data);
void strToVector(string str, vector<char>& data);
string replaceVector(std::vector<char>& data);