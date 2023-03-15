#include<iostream>

using namespace std;

void RunTask();

//定义一个队列类
class Queue {
private:
	int* queue; //用指针指向动态分配的数组空间
	int front; //指向队头
	int rear; //指向队尾
	int capacity; //记录数组的容量

public:
	Queue(int size); //构造函数，初始化队列为空，并分配数组空间
	~Queue(); //析构函数，释放数组空间
	bool isEmpty(); //判断队列是否为空
	bool isFull(); //判断队列是否已满
	void enqueue(int x);
	int dequeue();
	int getfront();//获取队首元素
	int getrear();
	void showQueue();

};

//构造函数，初始化队列为空，并分配数组空间

Queue::Queue(int Queuesize) {

	queue = new int[Queuesize]; //用new动态分配数组空间

	front = -1;
	rear = -1;

	capacity = Queuesize; //记录数组容量


}

//析构函数，释放数组空间

Queue::~Queue() {

	delete[] queue; //用delete释放数组空间

}

//判断队列是否为空

bool Queue::isEmpty() {

	return front == rear;

}

//判断队列是否已满

bool Queue::isFull() {

	return (rear + 1) % capacity == front;

}

//入队操作，向队尾添加元素

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

//出队操作，从队头删除元素，并返回该元素
int Queue::dequeue() {

	if (isEmpty()) {
		cout << "Queue is empty!" << endl;
		return -1;
	}

	front = (front + 1) % capacity;

	int x = queue[front];

	return x;

}

//显示当前队列中的所有元素，从对头到对尾依次输出

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

/*用一个长度为k的窗口在长度为n的整数数列上从左往右滑动，每次滑动一个单位，求出每次滑动后每个窗口里面所包含的数的最大值*/

int main() {
	RunTask();
	return 0;
}

void RunTask() {
	int DataSize, WindowSize;
	cin >> DataSize >> WindowSize;

	if (DataSize < WindowSize) {
		cout << "Error:窗口大小大于数列大小" << endl;
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

		if (i - WindowSize == queue->getfront())//窗口滑出时候
			queue->dequeue();

		if (i + 1 >= WindowSize)
			cout << data[queue->getfront()] << "  ";

	}
	delete queue;
	delete[] data;
}