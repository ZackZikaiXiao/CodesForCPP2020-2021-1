#ifndef NODE_H
#define NODE_H

template<typename T>
class Node
{
private:
	T m_data;
	Node* m_left = nullptr, * m_right = nullptr;
public:
	Node() = default;
	Node(const Node&);
	Node& operator=(const Node& rhs);
	Node(const T& data) :m_data(data) {}
	T& data() { return m_data; }
	T& data(T value) { m_data = value; return m_data; }
	Node* left() { return m_left; }
	Node* left(Node* node) { m_left = node; return m_left; }
	Node* right() { return m_right; }
	Node* right(Node* node) { m_right = node; return m_right; }
};

template<typename T>
Node<T>::Node(const Node& rhs) {
	m_data = rhs.data();
	m_left = rhs.left();
	m_right = rhs.right();
}
template<typename T>
Node<T>& Node<T>::operator=(const Node& rhs) {
	m_data = rhs.data();
	m_left = rhs.left();
	m_right = rhs.right();
	return *this;
}


#endif // NODE_H