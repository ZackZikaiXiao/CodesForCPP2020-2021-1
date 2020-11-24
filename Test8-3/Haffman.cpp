#include "Haffman.h"

void Haffman::encode() {
	/*1.������Ƶhashӳ��*/
	{
		unordered_map<char, int> mapStat;		// �ַ�ӳ�䵽����weight��λ��[0, size)
		for (auto it = m_inputTest.begin(); it != m_inputTest.end(); ++it) {
			if (mapStat.find(*it) != mapStat.end()) ++mapStat[*it];	// ���ַ�����Ƶ+1
			else mapStat[*it] = 1;
		}
		/*����Ȩֵ����Ͷ�����ָ������*/
		for (auto it = mapStat.begin(); it != mapStat.end(); ++it) {
			m_node.push_back(new Node<char>(it->first));
			m_weight.push_back(it->second);
		}
	}
	/*2.������������*/
	while (m_node.size() != 1) {		// ���Ϻϲ�
		int locArray[2] = { 0, 0 };// ����С����С
		int tmp = m_weight[0];
		for (int i = 0; i < m_weight.size(); ++i) {		// ��Сλ�û�ȡ
			if (m_weight[i] <= tmp) {
				tmp = m_weight[i];
				locArray[0] = locArray[1];
				locArray[1] = i;
			}
		}
		if (locArray[0] > locArray[1]) {		// ����λ�ã���С�Ҵ�
			locArray[0] = locArray[0] ^ locArray[1];
			locArray[1] = locArray[0] ^ locArray[1];
			locArray[0] = locArray[0] ^ locArray[1];
		}
		//m_node����
		Node<char>* ptr = new Node<char>(NULL);	// ���ַ�	ptrָ��Node��node�����ҽڵ�Ҳ��ָ��
		(*ptr).left(m_node[locArray[0]]);
		(*ptr).right(m_node[locArray[1]]);
		m_node[locArray[0]] = ptr;
		m_node.erase(m_node.begin() + locArray[1]);
		//m_weight����
		m_weight[locArray[0]] = m_weight[locArray[0]] + m_weight[locArray[1]];
		m_weight.erase(m_weight.begin() + locArray[1]);
	}
	/*3.������������hashman����*/
	//Node<char>* ptr = m_node[0];
	getCode(m_node[0], "");
}
template<typename T>
void Haffman::getCode(Node<T>* root, string s) {
	if ((*root).left() == nullptr && (*root).right() == nullptr) {	// �õ�Ҷ�ӽ��
		//cout << (*root).data() << ":\t" << s << endl;
		m_haffmanCode[(*root).data()] = s;
	}
	if ((*root).left()) {	 //��Ϊ��
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
		if ((*ptr).left() == nullptr && (*ptr).right() == nullptr) {	// �õ�Ҷ�ӽ��
			outputText.push_back((*ptr).data());
			ptr = m_node[0];
		}
	}
	cout << endl<< "DECODE:" << endl << outputText << endl;
	ofstream out(filename);
	if (out.is_open()) out << outputText;
	out.close();
}