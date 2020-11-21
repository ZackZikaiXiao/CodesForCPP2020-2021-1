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
	Stack<double> m_num; // 数字栈
	Stack<string> m_opr; // 运算符栈
	vector<string> m_tokenStream;
	// 知识, 得到运算符优先级
	int precedence(const string& s);
	void getTokenStream(vector<string> tokenStream) { m_tokenStream = tokenStream; }
	// 动作, 使用运算符栈和操作数栈顶的元素进行计算并修改两个栈
	void calculate();
	bool isNum(vector<string>::const_iterator& c) const;
	double readNum(vector<string>::const_iterator& c);
	double babyCalc(string exp);
	void brackDeal(int& preBrackLoc, int& subitBrackLoc);
public:
	// 无参构造函数
	Calculator() { m_opr.push("#"); };
	Calculator(Calculator& cclt) :m_dfa(cclt.m_dfa.m_identifier) { m_opr.push("#"); }
	DFA m_dfa;
	double doIt(string& exp);
};



