//
// Created by Zack on 2020/10/29.
//
#ifndef TEST7_2_SET_H
#define TEST7_2_SET_H
#include <iostream>
#include <vector>
using namespace std;

template <typename T> class Set;
template<typename T> ostream& operator<<(ostream&, const Set<T>&);

template<typename T>
class Set {
    vector<T> m_elems;
public:
    Set() = default;
    Set(const vector<T>& elem);
    bool is_elem(T);     // 是否为集合元素
    void insert(T);
    void erase(T);
    Set common(const Set& s);
    Set sum(const Set& s);
    int find(const T item);
    int size(){return this->m_elems.size();}
    void clear(){vector<T>().swap(this->m_elems);}
    void swap(Set& s){this->m_elems.swap(s.m_elems);}
    Set& operator = (const Set& s);
    Set(const Set& s);
    friend ostream& operator<< <T>(ostream& os, const Set<T>& s);
private:
    void selectionSort(vector<T>& arr);
};


template <typename T>
Set<T>::Set(const vector<T>& elem) {
    m_elems = vector<T>(elem.size());
    for (int i = 0; i < elem.size(); i++) {
        m_elems[i] = elem[i];
    }
}

template <typename T>
bool Set<T>::is_elem(T elem) {
    for (int i = 0; m_elems.size(); i++) {
        if (m_elems[i] == elem) return true;
    }
    return false;
}

template <typename T>
void Set<T>::insert(T elem) {
    m_elems.push_back(elem);
}

template <typename T>
void Set<T>::erase(T elem) {
    vector<T>::iterator itr = m_elems.begin();
    while (itr != m_elems.end()) {
        if (*itr == elem) itr = m_elems.erase(itr);
        else itr++;
    }
    //cout << "Elem " << elem << " not found!" << endl;
}

template <typename T>
Set<T> Set<T>::common(const Set<T>& s) {     // Step1:sort Step2:catch redundancy
    vector<T> tempArr(this->m_elems.size() + s.m_elems.size());
    vector<T> catchArr;
    for (int i = 0; i < this->m_elems.size(); i++) tempArr[i] = this->m_elems[i];
    for (int i = 0; i < s.m_elems.size(); i++) tempArr[i + this->m_elems.size()] = s.m_elems[i];
    this->selectionSort(tempArr);
    vector<T>::iterator itr = tempArr.begin();
    while (itr != tempArr.end() - 1) {
        if (*itr == *(itr + 1)) {
            catchArr.push_back(*itr);
            itr = tempArr.erase(itr);
        }
        else itr++;
    }
    return Set(catchArr);
}

template <typename T>
Set<T> Set<T>::sum(const Set<T>& s) {     // Step1:sort Step2:eliminate redundancy
    vector<T> tempArr(this->m_elems.size() + s.m_elems.size());
    for (int i = 0; i < this->m_elems.size(); i++) tempArr[i] = this->m_elems[i];
    for (int i = 0; i < s.m_elems.size(); i++) tempArr[i + this->m_elems.size()] = s.m_elems[i];
    this->selectionSort(tempArr);
    vector<T>::iterator itr = tempArr.begin();
    while (itr != tempArr.end() - 1) {
        if (*itr == *(itr + 1)) itr = tempArr.erase(itr);
        else itr++;
    }
    return Set(tempArr);
}

template <typename T>
int Set<T>::find(const T item) {        // -1: No element
    for(int i = 0; i < this->m_elems.size(); i++) {
       if(this->m_elems[i] == item) return i;
    }
    cout << "Element not found!" << endl;
    return -1;
}

template <typename T>
Set<T>& Set<T>::operator= (const Set<T>& s) {
    this->m_elems = vector<T>(s.m_elems.size());
    for (int i = 0; i < s.m_elems.size(); i++) this->m_elems[i] = s.m_elems[i];
    return *this;
}

template <typename T>
Set<T>::Set(const Set<T>& s) {
    this->m_elems = vector<T>(s.m_elems.size());
    for (int i = 0; i < s.m_elems.size(); i++) this->m_elems[i] = s.m_elems[i];
}

template <typename T>
ostream& operator<<(ostream& os, const Set<T>& s) {
    for (int i = 0; i < s.m_elems.size(); i++) os << s.m_elems[i] << "\t";
    return os;
}

template <typename T>
void Set<T>::selectionSort(vector<T>& arr) {
    int len = arr.size();
    int minIndex;
    T temp;
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
#endif //TEST7_2_SET_H

/*
 * cout链接错误：添加了10、11两行代码
 * https://blog.csdn.net/Mind_V/article/details/70228402?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.channel_param&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.channel_param
 * */