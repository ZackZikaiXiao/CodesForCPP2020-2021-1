constexpr auto MAX_INT = (((unsigned int)(-1))>>1);
#include <iostream>
using namespace std;

class Node
{
private:
	string m_name;
	string m_tel;
	string m_QQ;
	string m_address;
public:
	Node* m_next = nullptr;
	Node() = default;
	Node(Node& rhs);
	Node(string name, string tel, string QQ, string address):m_name(name), m_tel(tel), m_QQ(QQ), m_address(address) {};
	bool empty() { return m_name == ""; }
	Node& operator=(const Node& rhs);
	Node* next()const { return m_next; }
	string name()const { return m_name; }
	string tel()const { return m_tel; }
	string QQ()const { return m_QQ; }
	string address()const { return m_address; }
	Node& operator=(Node& rhs) {
		m_name = rhs.name();
		m_tel = rhs.tel();
		m_QQ = rhs.QQ();
		m_address = rhs.address();
		return *this;
	}
};


class hashTable{
private:
	Node* m_bucketList[65536];	// 0~65535
	int m_hasArray[65536] = { 0 };
	unsigned int hashFunction(const string& str);
public:
	hashTable() = default;
	void makePair(string key, Node& newPerson);
	void find(string name);
	void erase(string name);
};
