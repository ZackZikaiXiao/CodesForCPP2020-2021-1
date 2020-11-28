#include "hashTable.h"

Node& Node::operator=(const Node& rhs) {
	m_name = rhs.name();
	m_tel = rhs.tel();
	m_QQ = rhs.QQ();
	m_address = rhs.address();
	m_next = rhs.next();
	return*this;
}
Node::Node(Node& rhs) {
	m_name = rhs.name();
	m_tel = rhs.tel();
	m_QQ = rhs.QQ();
	m_address = rhs.address();
	m_next = rhs.next();
}


unsigned int hashTable::hashFunction(const string& str) {
	auto it = str.begin();
	unsigned int hash = 1315423911;
	while (it != str.end()) {
		hash ^= ((hash << 5) + *(it++) + (hash >> 2));
	}
	return (hash & 0x0000FFFF);
}

void hashTable::makePair(string key, Node& newPerson) {
	int loc = hashFunction(key);
	Node* tmp = new Node(newPerson);
	if (m_hasArray[loc] == 0) m_bucketList[loc] = tmp;
	else {
		Node* ptr = m_bucketList[loc];
		while (ptr->next()) ptr = ptr->next();
		ptr->m_next = tmp;
	}
	++m_hasArray[loc];
}

void hashTable::find(string nameIn) {
	int loc = hashFunction(nameIn);
	if (m_hasArray[loc] == 0) cout << "No people found!" << endl;
	else {
		Node* ptr = m_bucketList[loc];
		while (ptr->next()) {
			if (ptr->name() == nameIn) {
				cout << "name:\t" << ptr->name() << endl;
				cout << "tel:\t" << ptr->tel() << endl;;
				cout << "QQ:\t" << ptr->QQ() << endl;;
				cout << "address:\t" << ptr->address() << endl;;
			}
			ptr = ptr->next();
		}
		if (ptr->name() == nameIn) {
			cout << "name:\t" << ptr->name() << endl;
			cout << "tel:\t" << ptr->tel() << endl;;
			cout << "QQ:\t" << ptr->QQ() << endl;;
			cout << "address:\t" << ptr->address() << endl;;
		}
	}
}

void hashTable::erase(string nameIn) {
	int loc = hashFunction(nameIn);
	if (m_hasArray[loc] == 0) cout << "No people found!" << endl;
	else {
		Node* ptr = m_bucketList[loc];
		Node* preptr = ptr;
		Node* tmp;
		int count = 0;
		if (ptr->name() == nameIn) {		
			tmp = ptr;
			ptr = ptr->m_next;
			cout << "name:\t" << tmp->name() << endl;
			cout << "tel:\t" << tmp->tel() << endl;;
			cout << "QQ:\t" << tmp->QQ() << endl;;
			cout << "address:\t" << tmp->address() << endl;
			delete tmp;
		}
		else ptr = ptr->m_next;
		while (ptr) {     // ·Ç¿Õ
			if (ptr->name() == nameIn) {
				preptr->m_next = ptr->m_next;
				cout << "name:\t" << ptr->name() << endl;
				cout << "tel:\t" << ptr->tel() << endl;;
				cout << "QQ:\t" << ptr->QQ() << endl;;
				cout << "address:\t" << ptr->address() << endl;
				delete ptr;
				ptr = preptr->m_next;
			}
			if (ptr->m_next) ptr = ptr->m_next;
			if(preptr->m_next)preptr = preptr;
		}
	}
	--m_hasArray[loc];
}
