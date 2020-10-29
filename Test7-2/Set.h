//
// Created by Zack on 2020/10/29.
//
#ifndef TEST7_2_SET_H
#define TEST7_2_SET_H
#include <iostream>
#include <vector>
using namespace std;
class Set {
    vector<char> m_elems;
public:
    Set() = default;
    Set(const vector<char> &elem);
    bool is_elem(char);
    void insert(char);
    void erase(char);
    Set common(const Set &s);
    Set sum(const Set &s);
    Set& operator = (const Set &s);
    Set(const Set &s);
    friend ostream& operator<<(ostream &os, const Set &s);
};


#endif //TEST7_2_SET_H
