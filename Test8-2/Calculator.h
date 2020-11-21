// Calculator based on stack

#include "Stack.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "DFA.h"

using namespace std;


class Calculator {
private:
	Stack<double> m_num; // ����ջ
	Stack<string> m_opr; // �����ջ
	vector<string> m_tokenStream;
	// ֪ʶ, �õ���������ȼ�
	int precedence(const string& s);
	void getTokenStream(vector<string> tokenStream) { m_tokenStream = tokenStream; }
	// ����, ʹ�������ջ�Ͳ�����ջ����Ԫ�ؽ��м��㲢�޸�����ջ
	void calculate();
	bool isNum(vector<string>::const_iterator& c) const;
	double readNum(vector<string>::const_iterator& c);
	double babyCalc(string exp);
	void brackDeal(int& preBrackLoc, int& subitBrackLoc);
public:
	// �޲ι��캯��
	Calculator() { m_opr.push("#"); };
	Calculator(Calculator& cclt) :m_dfa(cclt.m_dfa.m_identifier) { m_opr.push("#"); }
	DFA m_dfa;
	double doIt(string& exp);
};



