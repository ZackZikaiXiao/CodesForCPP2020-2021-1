#pragma once
#include<iostream>
using namespace std;

template<typename T> class SList;
template<typename T> ostream& operator<<(ostream&, const SList<T>&);

template<typename T>
class Node {
	friend class SList<T>;
	T m_data;
	Node* m_next = nullptr;
public:
	Node(const Node& rhs) = delete;
	Node& operator =(const Node& rhs) = delete;
	Node(const T& val) :m_data(val) {	}
	const T& data()const { return m_data; }
	T& data() { return m_data; }
	Node* next() { return m_next; }
};

template<typename T>
class SList {
	Node<T>* m_head = nullptr;
	int m_size = 0;
public:
	~SList();
	void clear();
	int erase(); //删除第一次出现的元素
	void add(int val);
	void forward(int offset);
	int getSize() { return m_size; }
	int getVal() { return m_head->m_data; }
	SList() = default;
	SList(const SList&) = delete;
};

template<typename T>
SList<T>::~SList() {
	clear();
}

template<typename T>
void SList<T>::forward(int offset) {
	for (int i = 0; i < offset; ++i) {
		m_head = m_head->m_next;
	}
}

template<typename T>
void SList<T>::add(int val) {
	Node<T>* newNode = new Node<T>(val);
	if (!m_head) {	// 空表
		m_head = newNode;
		m_head->m_next = m_head;
	}
	else if (m_head->m_next == m_head) { // 一个元素
		newNode->m_next = m_head;
		m_head->m_next = newNode;
		m_head = newNode;
	}
	else{		
		forward(m_size - 1);
		newNode->m_next = m_head->m_next;
		m_head->m_next = newNode;
		m_head = m_head->m_next;
	}
	++m_size;
}

template<typename T>
void SList<T>::clear() {
	if (m_size == 0);
	else if (m_size == 1) {
		delete m_head;
		m_head = nullptr;
	}
	else {
		Node<T>* endNode = m_head;
		m_head = m_head->m_next;
		endNode->m_next = nullptr;
		Node<T>* tmp;
		while (!m_head->m_next) {
			tmp = m_head;
			m_head = m_head->m_next;
			delete tmp;
		}
	}
	m_size = 0;
}

template<typename T>
int SList<T>::erase() { 
	int val = m_head->m_data;
	if (m_head->m_next == m_head) {
		delete m_head;
		m_head = nullptr;
	}
	else {
		forward(m_size - 1);
		Node<T>* tmp = m_head->m_next;
		m_head->m_next = m_head->m_next->m_next;
		delete tmp;
		m_head = m_head->m_next;
	}
	--m_size;
	return val;
}
