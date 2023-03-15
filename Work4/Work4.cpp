#include<iostream>

using namespace std;

void RunTask();

//����һ��������
class Queue {
private:
	int* queue; //��ָ��ָ��̬���������ռ�
	int front; //ָ���ͷ
	int rear; //ָ���β
	int capacity; //��¼���������

public:
	Queue(int size); //���캯������ʼ������Ϊ�գ�����������ռ�
	~Queue(); //�����������ͷ�����ռ�
	bool isEmpty(); //�ж϶����Ƿ�Ϊ��
	bool isFull(); //�ж϶����Ƿ�����
	void enqueue(int x);
	int dequeue();
	int getfront();//��ȡ����Ԫ��
	int getrear();
	void showQueue();

};

//���캯������ʼ������Ϊ�գ�����������ռ�

Queue::Queue(int Queuesize) {

	queue = new int[Queuesize]; //��new��̬��������ռ�

	front = -1;
	rear = -1;

	capacity = Queuesize; //��¼��������


}

//�����������ͷ�����ռ�

Queue::~Queue() {

	delete[] queue; //��delete�ͷ�����ռ�

}

//�ж϶����Ƿ�Ϊ��

bool Queue::isEmpty() {

	return front == rear;

}

//�ж϶����Ƿ�����

bool Queue::isFull() {

	return (rear + 1) % capacity == front;

}

//��Ӳ��������β���Ԫ��

void Queue::enqueue(int x) {

	if (isFull()) {
		cout << "Queue is full!" << endl;
		return;
	}

	rear = (rear + 1) % capacity;

	queue[rear] = x;


}

int Queue::getrear() {
	if (isEmpty()) {
		cout << "Queue is empty!" << endl;
		return -1;
	}
	return queue[rear];
}

int Queue::getfront() {

	if (isEmpty()) {
		cout << "Queue is empty!" << endl;
		return -1;
	}

	return queue[(front + 1) % capacity];
}

//���Ӳ������Ӷ�ͷɾ��Ԫ�أ������ظ�Ԫ��
int Queue::dequeue() {

	if (isEmpty()) {
		cout << "Queue is empty!" << endl;
		return -1;
	}

	front = (front + 1) % capacity;

	int x = queue[front];

	return x;

}

//��ʾ��ǰ�����е�����Ԫ�أ��Ӷ�ͷ����β�������

void Queue::showQueue() {

	if (isEmpty()) {
		cout << "Queue is empty!" << endl;
		return;
	}

	cout << "The elements in the queue are: ";

	for (int i = (front + 1) % capacity; i != (rear + 1) % capacity; i = (i + 1) % capacity) {
		cout << queue[i] << " ";

	}

	cout << endl;

}

/*��һ������Ϊk�Ĵ����ڳ���Ϊn�����������ϴ������һ�����ÿ�λ���һ����λ�����ÿ�λ�����ÿ�������������������������ֵ*/

int main() {
	RunTask();
	return 0;
}

void RunTask() {
	int DataSize, WindowSize;
	cin >> DataSize >> WindowSize;

	if (DataSize < WindowSize) {
		cout << "Error:���ڴ�С�������д�С" << endl;
		return;
	}

	int* data = new int[DataSize];
	for (int i = 0; i < DataSize; i++)
	{
		cin >> data[i];
	}

	Queue* queue = new Queue(DataSize);
	for (int i = 0; i < DataSize; i++)
	{
		if (queue->isEmpty() || data[i]<=data[queue->getrear()]) {
			queue->enqueue(i);
		}
		else {
			while (!queue->isEmpty() && data[i] > data[queue->getrear()])
			{
				queue->dequeue();
			}
			queue->enqueue(i);
		}

		if (i - WindowSize == queue->getfront())//���ڻ���ʱ��
			queue->dequeue();

		if (i + 1 >= WindowSize)
			cout << data[queue->getfront()] << "  ";

	}
	delete queue;
	delete[] data;
}