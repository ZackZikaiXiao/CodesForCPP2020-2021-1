#include <iostream>
#include <fstream>
#include "Haffman.h"
#include <string>
/*
1.读取
2.词频统计
3.用两个vector来分别维护权值和树
*/
int main()
{
    /*1.读取*/
    ifstream readText("D:\\\\Codes\\cplusplus2020-2021-1\\code\\Test8.3\\haffman.txt", ios::in);
    string inputText;
    getline(readText, inputText);
    readText.close();
    /*编码*/
    Haffman hfm(inputText);
    hfm.encode();
    hfm.codeShow();
    hfm.write("encoded.txt");
    /*解码**/
    ifstream readCode("D:\\\\Codes\\cplusplus2020-2021-1\\code\\Test8.3\\encoded.txt", ios::in);
    string inputCode;
    getline(readCode, inputCode);
    readCode.close();
    hfm.decode(inputCode, "decoded.txt");
}
