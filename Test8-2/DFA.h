#pragma once
#ifndef DFA_H
#define DFA_H
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

class DFA {
private:
	vector<string> m_tokenStream;		// �ʷ�����������ӿ�
	unordered_map<string, int> m_operators;		// Ĭ��֧�ֵĲ��������ȼ�
	unordered_map<string, int> m_function;		// Ĭ��֧�ֵĺ���
	void init();
	bool isNumber(char& rhs) { return rhs >= '0' && rhs <= '9'; }
	bool isAlpha(char& rhs) { return rhs >= 'a' && rhs <= 'z' || rhs >= 'A' && rhs <= 'Z'; }
	void fail(string warning) { cout << warning << endl; }
	void EXCEPTION_HANDING();
public:
	DFA();
	DFA(unordered_map<string, double> identifier);
	~DFA() = default;
	unordered_map<string, double> m_identifier;	// �Զ������
	int catchExpIn(string expIn);
	int getPrecedence(string s) { return m_operators[s]; }
	void addID(string id, double value);	//����Զ������
	double getID(string id) { return m_identifier[id]; }
	void clearTokenStream() {vector<string>().swap(m_tokenStream); }
	void clearID() { m_identifier.clear(); }
	vector<string> getTokenStream() { return m_tokenStream; };		
	bool hasOP(const string& s) { return m_operators.find(s) != m_operators.end(); };
	bool hasFunc(const string& s) { return m_function.find(s) != m_function.end(); };
	bool hasID(const string& s) { return m_identifier.find(s) != m_identifier.end(); };
	void debugShow();
};

#endif // !DFA_H