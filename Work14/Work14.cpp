#include <iostream>
#include <queue>
using namespace std;


int adjust_loser_tree(int* heap, int* key_heap, int pos)
{
	int winner = pos;
	for (int i = pos; i > 0; i /= 2)
	{
		int father = heap[i / 2];
		if ((i == 1 && key_heap[father] > key_heap[winner]) || key_heap[father] < key_heap[winner] || (heap[father] < heap[winner] && key_heap[father] == key_heap[winner]))//when lose
		{
			int temp = winner;
			winner = heap[i / 2];
			heap[i / 2] = temp;
		}else if(i==1)
		{
			heap[0] = winner;
		}
	}
	return heap[0];
}


int main() {
	// 输入待排序关键码序列
	queue<int> nums;
	int n;
	while (cin.peek() != '\n')
	{
		cin >> n;
		nums.emplace(n);
	}

	// 输入堆的大小
	int heapSize;
	cin >> heapSize;

	int heapheight = heapSize*2;

	int* heap = new int[heapheight];
	int* key_heap = new int[heapheight];

	for (int i = 0; i < heapheight; ++i)
	{
		heap[i] = key_heap[i] = 0;
	}

	int p = 0;

	int runs = 1;

	for (int i = heapheight-1; i >= heapheight-heapSize; --i)
	{
		heap[i] = nums.front();
		key_heap[i] = runs;
		nums.pop();
		p = adjust_loser_tree(heap, key_heap, i);
	}

	int maxv;

	while (!nums.empty())
	{
		maxv = heap[p];
		cout << heap[p] << " ";
		heap[p] = nums.front();
		nums.pop();
		key_heap[p] = maxv < heap[p] ? runs : runs + 1;
		p = adjust_loser_tree(heap, key_heap, p);
		if (key_heap[p] != runs)
		{
			runs++;
			cout << endl;
		}
	}


	while (key_heap[p] != INT16_MAX)
	{
		cout << heap[p] << " ";
		heap[p] = INT16_MAX;
		key_heap[p] = INT16_MAX;
		p = adjust_loser_tree(heap, key_heap, p);
	}

	delete[] heap;
	delete[] key_heap;
	return 0;
}
