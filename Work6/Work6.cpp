#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
constexpr auto MAX_QUEUE_SIZE = 200;


typedef int ElemType;

typedef struct BiTNode {
	ElemType data;	
	BiTNode* lChild, * rChild;
}*BiTree;


typedef struct queue
{
	BiTNode array[MAX_QUEUE_SIZE];
	int front;
	int rear;
}SqQueue;

SqQueue* Init_CirQueue()
{
	SqQueue* Q = (SqQueue*)malloc(sizeof(SqQueue));
	if (!Q)
		exit(0);
	Q->front = Q->rear = 0;
	return(Q);
}


bool IsEmpty_Queue(SqQueue* Q)
{
	if (Q->front == Q->rear)
		return 1;       
	return 0;
}

bool IsFull_Queue(SqQueue* Q)
{
	if ((Q->rear + 1) % MAX_QUEUE_SIZE == Q->front)	
		return 1;
	return 0;
}

int Size_Queue(SqQueue* Q)
{
	return (Q->rear + MAX_QUEUE_SIZE - Q->front) % MAX_QUEUE_SIZE;
}

bool Push(SqQueue* Q, BiTNode e)
{
	if (IsFull_Queue(Q))	
	{
		printf("Insert: The queue is full.\n");
		return 1;
	}
	Q->array[Q->rear].data = e.data;   
	Q->array[Q->rear].lChild = e.lChild;
	Q->array[Q->rear].rChild = e.rChild;
	Q->rear = (Q->rear + 1) % MAX_QUEUE_SIZE;

	return 0;       
}

bool Pop(SqQueue* Q, BiTNode* x)
{
	if (IsEmpty_Queue(Q))	
	{
		printf("The queue is empty.\n");
		return 1;       
	}
	x->data = Q->array[Q->front].data;  
	x->lChild = Q->array[Q->front].lChild;
	x->rChild = Q->array[Q->front].rChild;
	Q->front = (Q->front + 1) % MAX_QUEUE_SIZE;

	return 0;
}


int CreateBiTree(BiTree* T)
{
	ElemType ch;
	ElemType temp;
	scanf_s("%d", &ch);
	temp = getchar();
	if (ch == -1)
		*T = NULL;
	else {
		*T = (BiTree)malloc(sizeof(BiTNode));
		if (!(*T))
			exit(-1);
		(*T)->data = ch;
		printf("输入%d的左子节点：", ch);
		CreateBiTree(&(*T)->lChild);
		printf("输入%d的右子节点：", ch);
		CreateBiTree(&(*T)->rChild);
	}return 1;
}

//先序遍历
void TraverseBiTree(BiTree T)
{
	if (T == NULL)return;
	printf("%d ", T->data);
	TraverseBiTree(T->lChild);
	TraverseBiTree(T->rChild);
}
//中序遍历
void InOrderBiTree(BiTree T){

	if (T == nullptr)
		return;
	InOrderBiTree(T->lChild);
	printf("%d ", T->data);
	InOrderBiTree(T->rChild);
}

//后续遍历
void PostOrderBiTree(BiTree T)
{
	if (T == nullptr)
		return;
	PostOrderBiTree(T->lChild);
	PostOrderBiTree(T->rChild);
	printf("%d ", T->data);
}
//深度
int TreeDeep(BiTree T)
{
	int deep = -1;
	if (T) {
		int leftdeep = TreeDeep(T->lChild);
		int rightdeep = TreeDeep(T->rChild);
		deep = leftdeep >= rightdeep ? leftdeep + 1 : rightdeep + 1;
	}return deep;
}

int TreeDeep_norecursion(BiTree T)
{
	int deep = -1;
	if (T) {
		SqQueue* Q = NULL;
		Q = Init_CirQueue();
		Push(Q, *T);
		while (!IsEmpty_Queue(Q))
		{
			int len = Size_Queue(Q);
			deep++;
			while (len--) {
				BiTNode temp;
				Pop(Q, &temp);
				if (temp.lChild)
					Push(Q, *temp.lChild);
				if (temp.rChild)
					Push(Q, *temp.rChild);
			}
		}
	}
	return deep;
}

//度数为1节点计数
int Degree1count(BiTree T)
{
	int num = 0;
	if (T == nullptr)
		return num;

	num += Degree1count(T->lChild) + Degree1count(T->rChild);

	if ((T->rChild == nullptr && T->lChild != nullptr) || (T->rChild != nullptr && T->lChild == nullptr))
		num += 1;

	return num;
}

int Degree1count_norecursion(BiTree T)
{
	int num = 0;
	if (T == nullptr)
		return num;
	SqQueue* queue = Init_CirQueue();
	BiTree p = T;
	while (p != nullptr)
	{
		if ((!p->lChild && p->rChild) || (p->lChild && !p->rChild))
			num++;
		if (p->lChild)
			Push(queue, *p->lChild);
		if (p->rChild)
			Push(queue, *p->rChild);
		if (IsEmpty_Queue(queue))
			break;
		Pop(queue, p);
	}

	return num;
}

/*
 * 1、	实现二叉树前序、中序、后序遍历的递归算法；
 * 2、	计算二叉树的深度（递归和非递归算法）；
 * 3、	统计二叉树度为1的节点个数（递归和非递归算法）；
 */

//main
int main(void)
{
	BiTree T;

	int deepth = -1, num = 0;
	printf("请输入第一个结点的值,-1表示没有对应子树:\n");
	CreateBiTree(&T);
	printf("先序遍历二叉树:\n");
	TraverseBiTree(T);
	printf("\n");
	printf("中序遍历二叉树:\n");
	InOrderBiTree(T);
	printf("\n");
	printf("后序遍历二叉树:\n");
	PostOrderBiTree(T);
	printf("\n");
	deepth = TreeDeep(T);
	printf("树的深度为:%d", deepth);
	printf("\n");
	deepth = TreeDeep_norecursion(T);
	printf("树的深度为:%d", deepth);
	printf("\n");
	num = Degree1count(T);
	printf("树的度为1的结点个数为:%d", num);
	printf("\n");
	num = Degree1count_norecursion(T);
	printf("树的度为1的结点个数为:%d", num);
	printf("\n");
	return 0;
}