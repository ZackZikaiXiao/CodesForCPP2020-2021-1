//
// Created by Zack on 2020/10/29.
//
#include "Set.h"
Set::Set(const vector<char>& elem) {
    m_elems = vector<char>(elem.size());
    for (int i = 0; i < elem.size(); i++) {
        m_elems[i] = elem[i];
    }
}
bool Set::is_elem(char elem) {
    for (int i = 0; m_elems.size(); i++) {
        if (m_elems[i] == elem) return true;
    }
    return false;
}
void Set::insert(char elem) {
    m_elems.push_back(elem);
}
void Set::erase(char elem) {
    vector<char>::iterator itr = m_elems.begin();
    while (itr != m_elems.end()) {
        if (*itr == elem) itr = m_elems.erase(itr);
        else itr++;
    }
    //cout << "Elem " << elem << " not found!" << endl;
}
Set Set::common(const Set& s) {     // Step1:sort Step2:catch redundancy
    vector<char> tempArr(this->m_elems.size() + s.m_elems.size());
    vector<char> catchArr;
    for (int i = 0; i < this->m_elems.size(); i++) tempArr[i] = this->m_elems[i];
    for (int i = 0; i < s.m_elems.size(); i++) tempArr[i + this->m_elems.size()] = s.m_elems[i];
    this->selectionSort(tempArr);
    vector<char>::iterator itr = tempArr.begin();
    while (itr != tempArr.end() - 1) {
        if (*itr == *(itr + 1)) {
            catchArr.push_back(*itr);
            itr = tempArr.erase(itr);
        }
        else itr++;
    }
    return Set(catchArr);
}
Set Set::sum(const Set& s) {     // Step1:sort Step2:eliminate redundancy
    vector<char> tempArr(this->m_elems.size() + s.m_elems.size());
    for (int i = 0; i < this->m_elems.size(); i++) tempArr[i] = this->m_elems[i];
    for (int i = 0; i < s.m_elems.size(); i++) tempArr[i + this->m_elems.size()] = s.m_elems[i];
    this->selectionSort(tempArr);
    vector<char>::iterator itr = tempArr.begin();
    while (itr != tempArr.end() - 1) {
        if (*itr == *(itr + 1)) itr = tempArr.erase(itr);
        else itr++;
    }
    return Set(tempArr);
}
Set& Set::operator= (const Set& s) {
    this->m_elems = vector<char>(s.m_elems.size());
    for (int i = 0; i < s.m_elems.size(); i++) this->m_elems[i] = s.m_elems[i];
    return *this;
}
Set::Set(const Set& s) {
    this->m_elems = vector<char>(s.m_elems.size());
    for (int i = 0; i < s.m_elems.size(); i++) this->m_elems[i] = s.m_elems[i];
}
ostream& operator<<(ostream& os, const Set& s) {
    for (int i = 0; i < s.m_elems.size(); i++) os << s.m_elems[i] << "\t";
    return os;
}
void Set::selectionSort(vector<char>& arr) {
    int len = arr.size();
    int minIndex, temp;
    for (int i = 0; i < len - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < len; j++) {
            if (arr[j] < arr[minIndex]) minIndex = j;
        }
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

