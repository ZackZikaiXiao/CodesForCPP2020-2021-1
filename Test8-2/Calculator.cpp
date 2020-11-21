#include "Calculator.h"

using namespace std;

int Calculator::precedence(const string& s) {
	return m_dfa.getPrecedence(s);
}

double Calculator::readNum(vector<string>::const_iterator& c) {
	string prefix, suffix;   // prefix  e/E suffix
	int position = -1;
	for (int i = 0; i < (*c).length(); i++) {	// 找e或E
		if ((*c)[i] == 'e' || (*c)[i] == 'E') { position = i; break; }
	}
	if (position == -1) {	//没找到
		prefix = *c;
		suffix = "0";
	}
	else {
		prefix = (*c).substr(0, position);
		suffix = (*c).substr(position + 1);
	}
	return stod(prefix) * pow(10, stod(suffix));
}

inline bool Calculator::isNum(vector<string>::const_iterator& c) const {		// c是vector<string>的迭代器，*c是一个string，(*c)[0]是该string的首元素
	return (*c)[0] >= '0' && (*c)[0] <= '9' || (*c)[0] == '-' || (*c)[0] == '+';
}
void Calculator::calculate() {
	double b = m_num.top();
	m_num.pop();
	double a = m_num.top();
	m_num.pop();
	if (m_opr.top() == "+")
		m_num.push(a + b);
	else if (m_opr.top() == "-")
		m_num.push(a - b);
	else if (m_opr.top() == "*")
		m_num.push(a * b);
	else if (m_opr.top() == "/")
		m_num.push(a / b);
	else if(m_opr.top() == "^")
		m_num.push(pow(a, b));
	m_opr.pop();
}

double Calculator::babyCalc(string exp) {
	Calculator cclt(*this);
	return cclt.doIt(exp);
}
void  Calculator::brackDeal(int& preBrackLoc, int& subitBrackLoc) {
	string inBrack;
	m_tokenStream.erase(m_tokenStream.begin() + preBrackLoc);	// 删除(
	subitBrackLoc--;
	m_tokenStream.erase(m_tokenStream.begin() + subitBrackLoc--);	// 删除)， 此时迭代器指向"("与")"
	for (auto it = m_tokenStream.begin() + preBrackLoc; it <= m_tokenStream.begin() + subitBrackLoc; it++) {	// 收集inBrack
		inBrack += *it;
	}
	while (preBrackLoc != subitBrackLoc) {		// 删除inBrack内容，迭代器重合
		m_tokenStream.erase(m_tokenStream.begin() + subitBrackLoc);
		subitBrackLoc--;
	}
	m_tokenStream[preBrackLoc] = to_string(babyCalc(inBrack));	// 用inBrack计算结果替代
}
double Calculator::doIt(string& exp) {
	/* "="处理 */
	int equalLoc = exp.find('=');
	string idName;
	if (equalLoc != exp.npos) {		// 找到了"="
		idName = exp.substr(0, equalLoc);
		exp.erase(0, equalLoc + 1);
	}
	/*分词*/
	m_dfa.catchExpIn(exp);  // 计算本次token
	m_num.clear();
	m_tokenStream = m_dfa.getTokenStream();	// 获取tokenstream
	/*函数处理(包括括号)，迭代*/
	while (1) {
		bool hasFunc;	//标志位
		int preBrackLoc = 0;
		int subitBrackLoc;
		for (auto itBrack = m_tokenStream.begin(); itBrack != m_tokenStream.end(); itBrack++) {
			if (*itBrack == "(") break;
			++preBrackLoc;
		}
		int brackCount = 0;		// 计数器，找到对应的)。遍历时，一次(加一，一次)减一，为0接收
		subitBrackLoc = preBrackLoc + 1;
		for (subitBrackLoc; subitBrackLoc < m_tokenStream.size(); subitBrackLoc++) {
			if (m_tokenStream[subitBrackLoc] == ")" && brackCount == 0) break;
			else if (m_tokenStream[subitBrackLoc] == "(") ++brackCount;
			else if (m_tokenStream[subitBrackLoc] == ")") --brackCount;
		}

		if (preBrackLoc != m_tokenStream.size()) {	// 有函数，普通函数或()
			if (preBrackLoc != 0 && m_dfa.hasFunc(m_tokenStream[preBrackLoc - 1])) {		// 普通函数
				double answer;
				if (m_tokenStream[preBrackLoc - 1] == "sin") {
					brackDeal(preBrackLoc, subitBrackLoc);		// sin a	pre = sub = a
					answer = stod(m_tokenStream[preBrackLoc]);	// 把a提出来，
					m_tokenStream.erase(m_tokenStream.begin() + preBrackLoc--);	// 把a删除，只剩sin
					m_tokenStream[preBrackLoc] = to_string(sin(answer));		// 用answer替换sin
				}
				else if (m_tokenStream[preBrackLoc - 1] == "cos") {
					brackDeal(preBrackLoc, subitBrackLoc);
					answer = stod(m_tokenStream[preBrackLoc]);
					m_tokenStream.erase(m_tokenStream.begin() + preBrackLoc--);
					m_tokenStream[preBrackLoc] = to_string(cos(answer));
				}
				else if (m_tokenStream[preBrackLoc - 1] == "tan") {
					brackDeal(preBrackLoc, subitBrackLoc);
					answer = stod(m_tokenStream[preBrackLoc]);
					m_tokenStream.erase(m_tokenStream.begin() + preBrackLoc--);
					m_tokenStream[preBrackLoc] = to_string(tan(answer));
				}
				else if (m_tokenStream[preBrackLoc - 1] == "sqrt") {
					brackDeal(preBrackLoc, subitBrackLoc);
					answer = stod(m_tokenStream[preBrackLoc]);
					m_tokenStream.erase(m_tokenStream.begin() + preBrackLoc--);
					m_tokenStream[preBrackLoc] = to_string(sqrt(answer));
				}
				else if (m_tokenStream[preBrackLoc - 1] == "pow") {
					int commaLoc;
					for (commaLoc = preBrackLoc; commaLoc <= subitBrackLoc; ++commaLoc) {
						if (m_tokenStream[commaLoc] == ",") break;
					}
					m_tokenStream[commaLoc] = ")";
					m_tokenStream.insert(m_tokenStream.begin() + commaLoc + 1, "(");
					++subitBrackLoc;
					int rBrackLength = subitBrackLoc - commaLoc;
					brackDeal(preBrackLoc, commaLoc);
					subitBrackLoc = commaLoc + rBrackLength;
					++commaLoc;
					brackDeal(commaLoc, subitBrackLoc);
					// 计算pow并更新m_tokenStream
					m_tokenStream[preBrackLoc] = to_string(pow(stod(m_tokenStream[preBrackLoc]), stod(m_tokenStream[subitBrackLoc])));
					m_tokenStream.erase(m_tokenStream.begin() + subitBrackLoc);
				}
			}
			else {		// ()函数
				brackDeal(preBrackLoc, subitBrackLoc);
			}
		}
		else break;
	}
	

	/*操作符和数字处理*/
	for (auto it = m_tokenStream.begin(); it != m_tokenStream.end();) {			// 一个个token扫描
		if (m_dfa.hasOP(*it)) {	//是操作符
			while (precedence(*it) <= precedence(m_opr.top())) {
				if (m_opr.top() == "#")
					break;
				calculate();
			}
			if (*it != ";")
				m_opr.push(*it);
			++it;
		}
		else if (isNum(it)) { m_num.push(readNum(it)); ++it; }		// 是数字
		else { m_num.push(m_dfa.getID(*it)); ++it; }		// 是自定义符号
	}

	if (equalLoc != exp.npos) {		// 有"="
		m_dfa.addID(idName, m_num.top());
	}
	return m_num.top();
}
