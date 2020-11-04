//
// Created by Zack on 2020/11/4.
//

#ifndef TEST7_3_MYVECTOR_H
#define TEST7_3_MYVECTOR_H
#include "iostream"
using namespace std;

template <typename T>
class MyVector{
    T* m_elems = new T[1000];
    int m_size = 0;
    int m_max = 1000;
public:
    MyVector() = default;     // 默认构造函数
    MyVector(T* arr, int len);      // 带参数构造函数
    MyVector(MyVector& myVector);       // 拷贝构造函数
    ~MyVector(){delete m_elems;}
    MyVector& operator=(const MyVector& myVector);    //  赋值运算符
    int size() {return this->m_size;}
    T& operator[](int loc);
    T& at(int loc);
    T& front();
    T& back();
    void push_back(T item);
    T& pop_back();
    void insert(T item, int loc);
    void erase();
    void clear();
    void sort();
    int binary_search(T item);
private:
    void resize(int capacity);
    bool isEmpty(){return this->m_size == 0;}
};
template <typename T>
MyVector<T>::MyVector(T* arr, int len){
    if(len <= 0) throw exception("length error");
    delete this->m_elems;
    this->m_elems = new T[len * 2];
    for(int i=0;i<len;i++) {
        this->m_elems[i] = arr[i];
        ++this->m_size;
    }
}
template <typename T>
MyVector<T>::MyVector(MyVector& myVector) {
    delete this->m_elems;
    this->m_size = myVector.m_size;
    this->m_max = myVector.m_max;
    this->m_elems = new T(myVector.m_max);
    for(int i=0;i<myVector.m_size;i++){
        this->m_elems[i] = myVector.m_elems[i];
    }
}
template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& myVector){
    delete this->m_elems;
    this->m_size = myVector.m_size;
    this->m_max = myVector.m_max;
    this->m_elems = new T(myVector.m_max);
    for(int i=0;i<myVector.m_size;i++){
        this->m_elems[i] = myVector.m_elems[i];
    }
    return *this;
}
template <typename T>
T& MyVector<T>::operator[](int loc){
    if(loc >= this->size()) throw exception("out of range");
    return m_elems[loc];
}
template <typename T>
T& MyVector<T>::front(){
    if(isEmpty()) throw exception("vector empty");
    return m_elems[0];
}
template <typename T>
T& MyVector<T>::back(){
    if(isEmpty()) throw exception("vector empty");
    return m_elems[m_size-1];
}
template <typename T>
void MyVector<T>::push_back(T item){
    if(m_size == m_max) resize(m_max * 2);
    m_elems[m_size++] = item;
}
template <typename T>
T& MyVector<T>::pop_back(){
    if(isEmpty()) throw exception(Vector Empty);
    T item = m_elems[--m_size];
    if(m_size == m_max/4) resize(m_max/2);
    return item;
}
template <typename T>
void MyVector<T>::insert(T item, int loc) {
    if(loc > m_size - 1) throw exception("Out of range!");
    if(m_size == m_max) resize(2 * m_max);    // 先判断满，再自增
    for(int i = m_size-1;i > loc; --i) {
        m_elems[i+1] = m_elems[i];
    }
    m_elems[loc] = item;
    ++m_size;
}
template <typename T>
void MyVector<T>::erase() {
    if(isEmpty()) throw exception("Vector Empty!");
    if(loc < 0 || loc > m_size - 1) throw exception("Out of range!");
    for(int i = loc;i < m_size;++i) {
        m_elems[i] = m_elems[i+1];
    }
    --m_size;
    if(m_size == m_max/4) resize(m_max/2);
}
template <typename T>
void MyVector<T>::clear() {     // 内存也清空, m_size置2
    delete m_elems;
    T* m_elems = new T[2];
    m_max = 2;
    m_size = 0;
}
template <typename T>
void MyVector<T>::sort() {
    for(int i = 0; i < m_size - 1; ++i) {
        for(int j = 0; j < m_size -1 -i; ++j) {
            if(m_elems[j] > m_elems[j+1]) {
                T temp = m_elems[j+1];
                m_elems[j+1] = m_elems[j];
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
    while(left <= right) {
        middle = (left + right) / 2;
        if(m_elems[middle] == item) return middle;
        else if ( m_elems[middle] > item) right = middle - 1;
        else left = middle + 1;
    }
    return -1;  // 查找失败
}
template <typename T>
void MyVector<T>::resize(int capacity) {
    if(capacity <= 0) throw exception("Range Error: capacity can't be zero or negative!");
    T* copy = new T[capacity];
    for(int i = 0;i < this->m_size;++i) {
        copy[i] = this->m_elems[i];
    }
    delete this->m_elems;
    this->m_elems = copy;
    this->m_max = capcacity;    // 注意已经改变了m_max
}
#endif //TEST7_3_MYVECTOR_H
