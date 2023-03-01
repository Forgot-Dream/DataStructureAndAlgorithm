#include<iostream>
using namespace std;

void LinearList();
void linkedlist_func();

//节点类
template<class T>
class Node {
public:
	Node* next;
	T value;
	Node(Node* next, T value) {
		this->next = next;
		this->value = value;
		cout << "Node create: " << value << endl;
	}
	Node(T value) {
		this->value = value;
		this->next = NULL;
		cout << "Node create: " << value << endl;
	}
	~Node() {
		if (this->next != NULL) {
			delete this->next;
		}
	}
};

//链表类
template<class T>
class LinkedList {
public:
	int Length() {
		return len;
	}
	void Add(T value);
	T GetFromIndex(int index);
	~LinkedList() {
		if (StartNode != NULL) {
			delete StartNode;
		}
	}
private:
	int len = 0;
	Node<T>* StartNode = nullptr;
	Node<T>* LastNode = nullptr;
};



//增加节点
template<class T>
inline void LinkedList<T>::Add(T value)
{
	if (LastNode == nullptr) {
		LastNode = new Node<T>(value);
		StartNode = LastNode;
	}
	else {
		LastNode->next = new Node<T>(NULL, value);
		LastNode = LastNode->next;
	}
	len++;
}

//获取值
template<class T>
inline T LinkedList<T>::GetFromIndex(int index)
{
	if (index > len - 1)
		return NULL;
	Node<T>* p = StartNode;
	for (int i = 0; i < index; i++) {
		p = p->next;
	}
	return p->value;
}



int main() {
	linkedlist_func();//使用链表
	LinearList();//使用线性表
	return 0;
}


void linkedlist_func() {
	LinkedList<int>* linklist_a = new LinkedList<int>();
	int number;
	for (;;)
	{
		cin >> number;
		linklist_a->Add(number);
		if (cin.peek() == '\n') {
			break;
		}
	}

	LinkedList<int>* linklist_b = new LinkedList<int>();
	for (;;)
	{
		cin >> number;
		linklist_b->Add(number);
		if (cin.peek() == '\n') {
			break;
		}
	}

	LinkedList<int>* linklist_c = new LinkedList<int>();
	int a = 0, b = 0;
	for (int i=0;i<(linklist_a->Length() + linklist_b->Length()) / 2; i++) {


		if ((b > linklist_b->Length() && a < linklist_a->Length()) || linklist_a->GetFromIndex(a + 1) > linklist_b->GetFromIndex(b + 1)) {
			linklist_c->Add(linklist_a->GetFromIndex(a));
			linklist_c->Add(linklist_a->GetFromIndex(a + 1));
			
			a += 2;
		}
		else if ((b < linklist_b->Length() && a > linklist_a->Length()) || linklist_a->GetFromIndex(a + 1) < linklist_b->GetFromIndex(b + 1)) {
			linklist_c->Add(linklist_b->GetFromIndex(b));
			linklist_c->Add(linklist_b->GetFromIndex(b + 1));
			b += 2;
		}
		else {
			int tmp = linklist_a->GetFromIndex(a) + linklist_b->GetFromIndex(b);
			if (tmp == 0) {
				a += 2;
				b += 2;
				continue;
			}
			linklist_c->Add(tmp);
			linklist_c->Add(linklist_a->GetFromIndex(a + 1));
			a += 2;
			b += 2;
		}

	}

	for (int j = 0; j < linklist_c->Length(); j++) {
		cout << linklist_c->GetFromIndex(j) << ' ';
	}

	delete linklist_a, linklist_b, linklist_c;

}





//使用顺序表结构进行的计算
void LinearList() {
	int* linearlist_1 = new int[100];
	int linearlist_1_len = 1;
	for (int i = 0;; i++, linearlist_1_len++)
	{
		cin >> linearlist_1[i];
		if (cin.peek() == '\n') {
			break;
		}
	}

	int* linearlist_2 = new int[100];
	int linearlist_2_len = 1;
	for (int i = 0;; i++, linearlist_2_len++)
	{
		cin >> linearlist_2[i];
		if (cin.peek() == '\n') {
			break;
		}
	}

	int* linearlist_3 = new int[100];
	int i = 0, a = 0, b = 0;
	for (;; i += 2) {


		if ((b > linearlist_2_len && a < linearlist_1_len) || linearlist_1[a + 1] > linearlist_2[b + 1]) {
			linearlist_3[i] = linearlist_1[a];
			linearlist_3[i + 1] = linearlist_1[a + 1];
			a += 2;
		}
		else if ((a > linearlist_1_len && b < linearlist_2_len) || linearlist_1[a + 1] < linearlist_2[b + 1]) {
			linearlist_3[i] = linearlist_2[b];
			linearlist_3[i + 1] = linearlist_2[b + 1];
			b += 2;
		}
		else {
			linearlist_3[i] = linearlist_1[a] + linearlist_2[b];
			linearlist_3[i + 1] = linearlist_2[b + 1];
			if (linearlist_3[i] == 0) {
				i -= 2;
			}
			a += 2;
			b += 2;
		}

		if (a > linearlist_1_len && b > linearlist_2_len) {
			break;
		}
	}
	for (int j = 0; j < i; j++) {
		cout << linearlist_3[j] << ' ';
	}

	delete[] linearlist_1, linearlist_2, linearlist_3;

}

