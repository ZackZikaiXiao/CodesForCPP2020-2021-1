//
// Created by Zack on 2020/11/4.
//

#ifndef TEST7_3_MYVECTOR_H
#define TEST7_3_MYVECTOR_H
#include "iostream"
using namespace std;

template <typename T>
class MyVector {
    T* m_elems = nullptr;
    int m_size;
    int m_max;
public:
    MyVector():m_elems(new T[2]), m_size(0), m_max(2) {};     // 默认构造函数
    MyVector(T* arr, int len);      // 带参数构造函数
    MyVector(MyVector& myVector);       // 拷贝构造函数
    MyVector(MyVector&& rhs);       // 拷贝构造函数(移动)
    ~MyVector() { delete[] m_elems; }
    MyVector& operator=(const MyVector& myVector);    //  赋值运算符
    MyVector& operator=(const MyVector&& rhs);    //  赋值运算符(移动)
    int size() { return this->m_size; }
    T operator[](int loc);
    T at(int loc);
    T front();
    T back();
    void push_back(T item);
    T pop_back();
    void insert(T item, int loc);
    void erase(int loc);
    void clear();
    void sort();
    int binary_search(T item);
    void debugshow();
private:
    void resize(int capacity);
    bool isEmpty() { return m_size == 0; }
};
template <typename T>
MyVector<T>::MyVector(T* arr, int len) :m_elems(new T[len * 2]), m_max(len * 2), m_size(len) {
    for (int i = 0; i < len; i++) {
        this->m_elems[i] = arr[i];
    }
}
template <typename T>
MyVector<T>::MyVector(MyVector& myVector) :m_elems(new T[myVector.m_max]), m_max(myVector.m_max), m_size(myVector.m_size) {    // 拷贝构造函数
    for (int i = 0; i < myVector.m_size; i++) {
        m_elems[i] = myVector.m_elems[i];
    }
}
template <typename T>
MyVector<T>::MyVector(MyVector&& rhs) :m_size(rhs.m_size), m_max(rhs.m_max, m_elems(rhs.m_elems)) { // 拷贝构造函数(移动)
    rhs.m_elems = nullptr;
}
template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& myVector) {      //  赋值运算符
    if (this != &myVector) {
        delete[] m_elems;
        m_size = myVector.m_size;
        m_max = myVector.m_max;
        m_elems = new T[myVector.m_max];
        for (int i = 0; i < myVector.m_size; i++) {
            m_elems[i] = myVector.m_elems[i];
        }
    }
    return *this;
}
template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector&& rhs) {    //  赋值运算符(移动)
    m_size = rhs.m_size;
    m_max = rhs.m_max;
    m_elems = rhs.m_elems;
    rhs.m_elems = nullptr;
    return *this;
}
template <typename T>
T MyVector<T>::operator[](int loc) {
    try {
        if (loc >= size()) throw out_of_range("out of range");
    }
    catch (out_of_range err) {
        cout << err.what() << endl;
        return false;
    }
    return m_elems[loc];
}
template <typename T>
T MyVector<T>::at(int loc) {
    try {
        if (isEmpty()) throw exception("vector empty");
    }
    catch (out_of_range err) {
        cout << err.what() << endl;
        return false;
    }
    return m_elems[loc];
}
template <typename T>
T MyVector<T>::front() {
    try {
        if (isEmpty()) throw exception("vector empty");
    }
    catch (out_of_range err) {
        cout << err.what() << endl;
        return false;
    }
    return m_elems[0];
}
template <typename T>
T MyVector<T>::back() {
    try {
        if (isEmpty()) throw out_of_range("vector empty");
    }
    catch (out_of_range err) {
        cout << err.what() << endl;
        return false;
    }
    return m_elems[m_size - 1];
}
template <typename T>
void MyVector<T>::push_back(T item) {
    if (m_size == m_max) resize(m_max * 2);
    m_elems[m_size++] = item;
}
template <typename T>
T MyVector<T>::pop_back() {
    try {
        if (isEmpty()) throw out_of_range("Vector Empty");
    }
    catch (out_of_range err) {
        cout << err.what() << endl;
        return false;
    }
    T item = m_elems[--m_size];
    if (m_size == m_max / 4) resize(m_max / 2);
    return item;
}
template <typename T>
void MyVector<T>::insert(T item, int loc) {         // loc is in [0, m_size] of vector, considering inserting a occupation.
    try {
        if (loc > m_size || loc < 0) throw out_of_range("Out of range!");
    }
    catch (out_of_range err) {
        cout << err.what() << endl;
        return;
    }
    if (m_size == m_max) resize(2 * m_max);    // 先判断满，再自增
    for (int i = m_size - 1; i >= loc; --i) {
        m_elems[i + 1] = m_elems[i];
    }
    m_elems[loc] = item;
    ++m_size;
}
template <typename T>
void MyVector<T>::erase(int loc) {
    try {
        if (isEmpty()) throw out_of_range("Vector Empty!");
        if (loc < 0 || loc > m_size - 1) throw out_of_range("Out of range!");
    }
    catch (out_of_range err) {
        cout << err.what() << endl;
        return;
    }
    for (int i = loc; i < m_size - 1; ++i) {
        m_elems[i] = m_elems[i + 1];
    }
    --m_size;
    if (m_size == m_max / 4) resize(m_max / 2);
}
template <typename T>
void MyVector<T>::clear() {     // 内存也清空, m_size置2
    delete[] m_elems;
    T* m_elems = new T[2];
    m_max = 2;
    m_size = 0;
}
template <typename T>
void MyVector<T>::sort() {
    for (int i = 0; i < m_size - 1; ++i) {
        for (int j = 0; j < m_size - 1 - i; ++j) {
            if (m_elems[j] > m_elems[j + 1]) {
                T temp = m_elems[j + 1];
                m_elems[j + 1] = m_elems[j];
                m_elems[j] = temp;
            }
        }
    }
}
template <typename T>
int MyVector<T>::binary_search(T item) {
    this->sort();
    int left = 0;
    int right = m_size - 1;
    int middle;
    while (left <= right) {
        middle = (left + right) / 2;
        if (m_elems[middle] == item) return middle;
        else if (m_elems[middle] > item) right = middle - 1;
        else left = middle + 1;
    }
    return -1;  // 查找失败
}
template <typename T>
void MyVector<T>::resize(int capacity) {
    try {
        if (capacity <= 0) throw exception("Range Error: capacity can't be zero or negative!");
    }
    catch (exception err) {
        cout << err.what() << endl;
        return;
    }

    T* copy = new T[capacity];
    for (int i = 0; i < m_size; ++i) {
        copy[i] = m_elems[i];
    }
    delete[] this->m_elems;
    m_elems = copy;
    m_max = capacity;    // 注意已经改变了m_max
}
template <typename T>
void MyVector<T>::debugshow() {
    for (int i = 0; i < m_size; ++i) cout << m_elems[i] << " ";
    cout << endl;
}
#endif //TEST7_3_MYVECTOR_H
