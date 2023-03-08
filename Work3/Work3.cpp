#include <iostream>
#include "Work3.h"

using namespace std;

void Compute();

template<class T>
Node<T>::~Node() {

#ifdef DEBUG
	cout << "[-] Node  Value: " << value << endl;
#endif

	if (prev != nullptr) {
		delete prev;
	}
}

template<class T>
Node<T>::Node(T value) {

#ifdef DEBUG
	cout << "[+] Node  Value: " << value << endl;
#endif

	this->value = value;
	this->prev = nullptr;

}

template<class T>
void Stack<T>::clear() {
	if (TopNode != nullptr) {
		delete TopNode;
		TopNode = nullptr;
		Size = 0;
	}
}

template<class T>
bool Stack<T>::push(const T value)
{

#ifdef DEBUG
	cout << "[+] Stack  Value: " << value << endl;
#endif

	if (Size == 0) {
		TopNode = new Node<T>(value);
	}
	else {
		Node<T>* p = new Node<T>(value);
		p->prev = TopNode;
		TopNode = p;
	}
	Size++;
	return true;
}

template<class T>
T Stack<T>::pop()
{

#ifdef DEBUG
	cout << "[-] Stack  Value: " << TopNode->value << endl;
#endif

	if (Size > 0) {
		T value = TopNode->value;
		Node<T>* p = TopNode;
		TopNode = p->prev;
		p ->prev = nullptr;
		delete p;
		return value;
	}
	else {
		return NULL;
	}
}

template<class T>
T Stack<T>::top()
{
	if (Size > 0) {
		return TopNode->value;
	}
	else {
		return NULL;
	}
}

template<class T>
bool Stack<T>::isEmpty()
{
	return Size == 0 ? true : false;
}


int main() {
	Compute();
	return 0;

}

void Compute() {
	Stack<int>* stack = new Stack<int>();
	char c;
	int n;
	while (true) {//按规范输入就没毛病 未处理异常输入
		cin >> c;
		if (c == '#' || !cin)
			break;
		switch (c)
		{
		case '+':
			stack->push(stack->pop() + stack->pop());
			break;
		case '-':
			stack->push(stack->pop() - stack->pop());
			break;
		case '*':
			stack->push(stack->pop() * stack->pop());
			break;
		case '/':
			stack->push(stack->pop() / stack->pop());
			break;
		default:
			cin.putback(c);
			cin >> n;
			stack->push(n);
			break;
		}
	}
	cout << stack->pop();
	delete stack;
}