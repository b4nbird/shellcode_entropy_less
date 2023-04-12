#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
#pragma warning(disable:4996)

//transfer data to string
string hexStr(unsigned char* data, int len)
{
    std::string result;
    char hex[3];
    for (int i = 0; i < len - 1; i++)
    {
        sprintf_s(hex, "%02x", data[i]);
        result += hex;
    }
    return result;
}


//transfer str to array
void strToVector(string str, vector<char>& data) {
    strcpy(data.data(), str.c_str());
}

//wordlist
string digitToWord(char digit) {

    switch (digit) {
    case '1': return "one";
    case '2': return "two";
    case '3': return "three";
    case '4': return "four";
    case '5': return "five";
    case '6': return "six";
    case '7': return "seven";
    case '8': return "eight";
    case '9': return "nine";
    case '0': return "zero";
    default: return "";
    }
}

string letterToWord(char letter) {
    switch (letter) {
    case 'a': return "apple";
    case 'b': return "ban";
    case 'c': return "cat";
    case 'd': return "date";
    case 'e': return "egg";
    case 'f': return "fig";
    case 'g': return "get";
    case 'h': return "hat";
    case 'i': return "ice";
    case 'j': return "jet";
    case 'k': return "kiwi";
    case 'l': return "lemon";
    case 'm': return "mango";
    case 'n': return "net";
    case 'o': return "orange";
    case 'p': return "pear";
    case 'q': return "quince";
    case 'r': return "raspect";
    case 's': return "strawberry";
    case 't': return "tank";
    case 'u': return "ugly";
    case 'v': return "victory";
    case 'w': return "water";
    case 'x': return "xigua";
    case 'y': return "yes";
    case 'z': return "zen";
    default: return "";
    }
}

string replaceVector(vector<char>& data) {
    string word;
    string fina;
    for (auto& c : data) {
        if (isdigit(c)) {
            word = digitToWord(c);
        }
        else if (isalpha(c)) {
            word = letterToWord(c);
        }
        if (!word.empty()) {
            fina += word + ' ';
        }
    }
    return fina;
}