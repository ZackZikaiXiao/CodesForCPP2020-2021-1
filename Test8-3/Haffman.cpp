#include "Haffman.h"

void Haffman::encode() {
	/*1.建立词频hash映射*/
	{
		unordered_map<char, int> mapStat;		// 字符映射到储存weight的位置[0, size)
		for (auto it = m_inputTest.begin(); it != m_inputTest.end(); ++it) {
			if (mapStat.find(*it) != mapStat.end()) ++mapStat[*it];	// 有字符，词频+1
			else mapStat[*it] = 1;
		}
		/*创造权值数组和二叉树指针数组*/
		for (auto it = mapStat.begin(); it != mapStat.end(); ++it) {
			m_node.push_back(new Node<char>(it->first));
			m_weight.push_back(it->second);
		}
	}
	/*2.构建哈夫曼树*/
	while (m_node.size() != 1) {		// 不断合并
		int locArray[2] = { 0, 0 };// 次最小、最小
		int tmp = m_weight[0];
		for (int i = 0; i < m_weight.size(); ++i) {		// 最小位置获取
			if (m_weight[i] <= tmp) {
				tmp = m_weight[i];
				locArray[0] = locArray[1];
				locArray[1] = i;
			}
		}
		if (locArray[0] > locArray[1]) {		// 交换位置，左小右大
			locArray[0] = locArray[0] ^ locArray[1];
			locArray[1] = locArray[0] ^ locArray[1];
			locArray[0] = locArray[0] ^ locArray[1];
		}
		//m_node处理
		Node<char>* ptr = new Node<char>(NULL);	// 空字符	ptr指向Node，node的左右节点也是指针
		(*ptr).left(m_node[locArray[0]]);
		(*ptr).right(m_node[locArray[1]]);
		m_node[locArray[0]] = ptr;
		m_node.erase(m_node.begin() + locArray[1]);
		//m_weight处理
		m_weight[locArray[0]] = m_weight[locArray[0]] + m_weight[locArray[1]];
		m_weight.erase(m_weight.begin() + locArray[1]);
	}
	/*3.遍历树，建立hashman编码*/
	//Node<char>* ptr = m_node[0];
	getCode(m_node[0], "");
}
template<typename T>
void Haffman::getCode(Node<T>* root, string s) {
	if ((*root).left() == nullptr && (*root).right() == nullptr) {	// 得到叶子结点
		//cout << (*root).data() << ":\t" << s << endl;
		m_haffmanCode[(*root).data()] = s;
	}
	if ((*root).left()) {	 //左不为空
		getCode(root->left(), s + "0");
	}
	if ((*root).right()) {
		getCode(root->right(), s + "1");
	}
}

void Haffman::codeShow() {
	cout << "CODESHOW:" << endl;
	for (auto ptr = m_haffmanCode.begin(); ptr != m_haffmanCode.end(); ++ptr) {
		cout << (*ptr).first << ":\t" << (*ptr).second << endl;
	}
}

void Haffman::write(string filename) {
	string s;
	for (auto it = m_inputTest.begin(); it != m_inputTest.end(); ++it) {
		s += m_haffmanCode[*it];
	}
	ofstream out(filename);
	cout << endl << "ENCODE:" << endl << s << endl;
	if (out.is_open()) out << s;
	out.close();
}

void Haffman::decode(string inputCode, string filename) {
	Node<char>* ptr = m_node[0];
	string outputText = "";
	for (auto it = inputCode.begin(); it != inputCode.end(); ++it) {
		if (*it == '0') { ptr = (*ptr).left(); }
		else if (*it == '1') { ptr = (*ptr).right(); }
		if ((*ptr).left() == nullptr && (*ptr).right() == nullptr) {	// 得到叶子结点
			outputText.push_back((*ptr).data());
			ptr = m_node[0];
		}
	}
	cout << endl<< "DECODE:" << endl << outputText << endl;
	ofstream out(filename);
	if (out.is_open()) out << outputText;
	out.close();
}