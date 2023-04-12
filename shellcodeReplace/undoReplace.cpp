#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "transfer.h"
#include <vector>


pair<unsigned char*, int> undoShellcode(string shellcode) {

    const char* numList[10] = { "zero","one", "two", "three", "four", "five", "six", "seven", "eight" , "nine" };
    //将shellcode以空格为间隔分割为新的数组
    string space_delimiter = " ";
    vector<string> words{};
    size_t pos = 0;
    while ((pos = shellcode.find(space_delimiter)) != string::npos) {
        words.push_back(shellcode.substr(0, pos));
        shellcode.erase(0, pos + space_delimiter.length());
    }
    //将单词还原成字符
    vector<string> new_words;
    for (auto i : words)
    {
        bool found = false;
        for (int j = 0; j < 10; j++)
        {
            if (i == numList[j])
            {
                new_words.push_back(to_string(j));
                found = true;
                break;
            }
        }
        if (!found)
        {
            new_words.push_back(i.substr(0, 1));
        }
    }
    string decrypt_str;
    for (auto i : new_words)
    {
        decrypt_str += i;
    }
    //转换成十六进制payload
    const int len = decrypt_str.length() / 2;
    unsigned char* my_payload = new unsigned char[len];

    for (int i = 0; i < len; i++) {
        std::string byteString = decrypt_str.substr(i * 2, 2);
        unsigned char byte = (unsigned char)std::stoi(byteString, nullptr, 16);
        my_payload[i] = byte;
    }
    cout << "shellcode还原成功：" << endl;
    for (int i = 0; i < len; i++) {
        printf("\\x%02x", my_payload[i]);
    }
    return make_pair(my_payload, len);
}