#pragma once

template<class T>
class Node {
public:
	Node<T>* prev;
	T value;
	~Node();
	Node(T);
};


template<class T>
class Stack {
public:
	void clear();
	bool push(const T value);
	T pop();
	T top();
	bool isEmpty();
private:
	Node<T>* TopNode;
	int Size = 0;
};