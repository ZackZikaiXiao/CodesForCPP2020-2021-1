#include "Calculator.h"

using namespace std;

int Calculator::precedence(const string& s) {
	return m_dfa.getPrecedence(s);
}

double Calculator::readNum(vector<string>::const_iterator& c) {
	string prefix, suffix;   // prefix  e/E suffix
	int position = -1;
	for (int i = 0; i < (*c).length(); i++) {	// ��e��E
		if ((*c)[i] == 'e' || (*c)[i] == 'E') { position = i; break; }
	}
	if (position == -1) {	//û�ҵ�
		prefix = *c;
		suffix = "0";
	}
	else {
		prefix = (*c).substr(0, position);
		suffix = (*c).substr(position + 1);
	}
	return stod(prefix) * pow(10, stod(suffix));
}

inline bool Calculator::isNum(vector<string>::const_iterator& c) const {		// c��vector<string>�ĵ�������*c��һ��string��(*c)[0]�Ǹ�string����Ԫ��
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
	m_tokenStream.erase(m_tokenStream.begin() + preBrackLoc);	// ɾ��(
	subitBrackLoc--;
	m_tokenStream.erase(m_tokenStream.begin() + subitBrackLoc--);	// ɾ��)�� ��ʱ������ָ��"("��")"
	for (auto it = m_tokenStream.begin() + preBrackLoc; it <= m_tokenStream.begin() + subitBrackLoc; it++) {	// �ռ�inBrack
		inBrack += *it;
	}
	while (preBrackLoc != subitBrackLoc) {		// ɾ��inBrack���ݣ��������غ�
		m_tokenStream.erase(m_tokenStream.begin() + subitBrackLoc);
		subitBrackLoc--;
	}
	m_tokenStream[preBrackLoc] = to_string(babyCalc(inBrack));	// ��inBrack���������
}
double Calculator::doIt(string& exp) {
	/* "="���� */
	int equalLoc = exp.find('=');
	string idName;
	if (equalLoc != exp.npos) {		// �ҵ���"="
		idName = exp.substr(0, equalLoc);
		exp.erase(0, equalLoc + 1);
	}
	/*�ִ�*/
	m_dfa.catchExpIn(exp);  // ���㱾��token
	m_num.clear();
	m_tokenStream = m_dfa.getTokenStream();	// ��ȡtokenstream
	/*��������(��������)������*/
	while (1) {
		bool hasFunc;	//��־λ
		int preBrackLoc = 0;
		int subitBrackLoc;
		for (auto itBrack = m_tokenStream.begin(); itBrack != m_tokenStream.end(); itBrack++) {
			if (*itBrack == "(") break;
			++preBrackLoc;
		}
		int brackCount = 0;		// ���������ҵ���Ӧ��)������ʱ��һ��(��һ��һ��)��һ��Ϊ0����
		subitBrackLoc = preBrackLoc + 1;
		for (subitBrackLoc; subitBrackLoc < m_tokenStream.size(); subitBrackLoc++) {
			if (m_tokenStream[subitBrackLoc] == ")" && brackCount == 0) break;
			else if (m_tokenStream[subitBrackLoc] == "(") ++brackCount;
			else if (m_tokenStream[subitBrackLoc] == ")") --brackCount;
		}

		if (preBrackLoc != m_tokenStream.size()) {	// �к�������ͨ������()
			if (preBrackLoc != 0 && m_dfa.hasFunc(m_tokenStream[preBrackLoc - 1])) {		// ��ͨ����
				double answer;
				if (m_tokenStream[preBrackLoc - 1] == "sin") {
					brackDeal(preBrackLoc, subitBrackLoc);		// sin a	pre = sub = a
					answer = stod(m_tokenStream[preBrackLoc]);	// ��a�������
					m_tokenStream.erase(m_tokenStream.begin() + preBrackLoc--);	// ��aɾ����ֻʣsin
					m_tokenStream[preBrackLoc] = to_string(sin(answer));		// ��answer�滻sin
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
					// ����pow������m_tokenStream
					m_tokenStream[preBrackLoc] = to_string(pow(stod(m_tokenStream[preBrackLoc]), stod(m_tokenStream[subitBrackLoc])));
					m_tokenStream.erase(m_tokenStream.begin() + subitBrackLoc);
				}
			}
			else {		// ()����
				brackDeal(preBrackLoc, subitBrackLoc);
			}
		}
		else break;
	}
	

	/*�����������ִ���*/
	for (auto it = m_tokenStream.begin(); it != m_tokenStream.end();) {			// һ����tokenɨ��
		if (m_dfa.hasOP(*it)) {	//�ǲ�����
			while (precedence(*it) <= precedence(m_opr.top())) {
				if (m_opr.top() == "#")
					break;
				calculate();
			}
			if (*it != ";")
				m_opr.push(*it);
			++it;
		}
		else if (isNum(it)) { m_num.push(readNum(it)); ++it; }		// ������
		else { m_num.push(m_dfa.getID(*it)); ++it; }		// ���Զ������
	}

	if (equalLoc != exp.npos) {		// ��"="
		m_dfa.addID(idName, m_num.top());
	}
	return m_num.top();
}
