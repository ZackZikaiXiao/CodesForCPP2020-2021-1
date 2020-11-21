#include "DFA.h"
DFA::DFA() {
	init();
}
DFA::DFA(unordered_map<string, double> identifier) {
	for (auto& v : identifier) m_identifier[v.first] = v.second;	// 自定义操作符的继承
	init();
}
void DFA::init() {
	m_operators["="] = -1;
	m_operators[";"] = 0;
	m_operators["#"] = 1;
	m_operators["+"] = 2;
	m_operators["-"] = 2;
	m_operators["%"] = 3;
	m_operators["*"] = 4;
	m_operators["/"] = 4;
	m_operators["^"] = 5;
	m_operators["("] = -1;
	m_operators[")"] = -1;
	m_operators[","] = -1;

	m_function["sin"] = -1;
	m_function["cos"] = -1;
	m_function["tan"] = -1;
	m_function["sqrt"] = -1;
	m_function["pow"] = -1;
}
int DFA::catchExpIn(string expIn) {
	clearTokenStream();	// 清理已有token
	if (expIn[expIn.size() - 1] != ';') expIn.push_back(';'); // 尾部加上;
	int state = 0; // start 
	string tmpStr;	// 暂存迭代器遍历到的字符
	string itStr;	// 暂存当前字符
	//int count = 0;	//计数器，用来报错时定位
	for (auto it = expIn.begin(); it != expIn.end();) {		// 对于每一个字母
		itStr = *it;
		if (itStr == "\t" || itStr == " ") { ++it; continue; }	//忽略空格
		switch (state) {
		case 0:
			if (m_operators.find(itStr) != m_operators.end()) { state = 12; break; }
			else if (isAlpha(*it)) { tmpStr.push_back(*it); state = 10; ++it; break; }
			else if (isNumber(*it)) { tmpStr.push_back(*it); state = 1; ++it; break; }
			else { fail("字符 " + itStr + " 未定义!"); state = 13; break; };
		case 1:
			if (isNumber(*it)) { tmpStr.push_back(*it); state = 1; ++it; break; }
			else if (*it == '.') { tmpStr.push_back(*it); state = 2; ++it; break; }
			else { state = 7; break; }
		case 2:
			if (isNumber(*it)) { tmpStr.push_back(*it); state = 3; ++it; break; }
			else { fail("数字输入错误！(字符" + itStr + "异常！)"); state = 13;  break; }
		case 3:
			if (isNumber(*it)) { tmpStr.push_back(*it); ++it; break; }
			else if (*it == 'e' || *it == 'E') { tmpStr.push_back(*it); state = 4; ++it; break; }
			else { state = 8; break; }
		case 4:
			if (*it == '+' || *it == '-') { tmpStr.push_back(*it); state = 5; ++it; break; }
			else if (isNumber(*it)) { tmpStr.push_back(*it); state = 6; ++it; break; }
			else { fail("数字输入错误！(字符" + itStr + "异常！)"); state = 13;  break; }
		case 5:
			if (isNumber(*it)) { tmpStr.push_back(*it); state = 6; ++it; break; }
			else { fail("数字输入错误！(字符" + itStr + "异常！)"); state = 13;  break; }
		case 6:
			if (isNumber(*it)) { tmpStr.push_back(*it); ++it; break; }
			else { state = 9; break; }
		case 7:
			m_tokenStream.push_back(tmpStr);
			tmpStr = "";
			state = 0;
			break;
		case 8:
			m_tokenStream.push_back(tmpStr);
			tmpStr = "";
			state = 0;
			break;
		case 9:
			m_tokenStream.push_back(tmpStr);
			tmpStr = "";
			state = 0;
			break;
		case 10:
			if (isAlpha(*it) || isNumber(*it)) { tmpStr.push_back(*it); ++it; break; }
			else { state = 11; break; }
		case 11:
			if (m_operators.find(tmpStr) != m_operators.end()) { // 先检查是否为默认支持的操作
				m_tokenStream.push_back(tmpStr);
				tmpStr = "";
				state = 0;
				break;
			}
			else if (m_function.find(tmpStr) != m_function.end()) {	// 再检查是否为函数
				m_tokenStream.push_back(tmpStr);
				tmpStr = "";
				state = 0;
				break;
			}
			else if (m_identifier.find(tmpStr) != m_identifier.end()) {	// 再检查是否为自定义变量
				m_tokenStream.push_back(tmpStr);
				tmpStr = "";
				state = 0;
				break;
			}
			else {
				fail("标识符" + tmpStr + "未定义！");
				state = 13;
				break;
			}
		case 12:
			m_tokenStream.push_back(itStr);
			++it;
			state = 0;
			break;
		case 13: // 异常处理
			//EXCEPTION_HANDING();
			throw exception("请重新输入:");
		}
	}
	return false;
}

void DFA::debugShow() {
	for (int i = 0; i < m_tokenStream.size(); ++i) cout << m_tokenStream[i] << " ";
	cout << endl;
	clearTokenStream();
}

void DFA::EXCEPTION_HANDING() {
	clearTokenStream();
	string exp;
	cout << "请重新输入:" << endl;
	cout << ">>";
	getline(cin, exp);
	catchExpIn(exp);
}

void DFA::addID(string id, double value) { 
	string::iterator it;
	for (it = id.begin(); it < id.end(); it++) {
		if (*it == ' ') {
			id.erase(it);
			it--;
		}
		if (*it == '\t') {
			id.erase(it);
			id.erase(it);
			it--;
		}
	}
	m_identifier[id] = value; 
}