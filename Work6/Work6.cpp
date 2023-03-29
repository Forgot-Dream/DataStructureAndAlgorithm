#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
constexpr auto MAX_QUEUE_SIZE = 200;


typedef int ElemType;
//��������
//����������ṹ
typedef struct BiTNode {
	ElemType data;	//������struct BiTNode
	BiTNode* lChild, * rChild;	//����������
}*BiTree;


typedef struct queue
{
	BiTNode array[MAX_QUEUE_SIZE];
	int front;
	int rear;
}SqQueue;

//ѭ�����л�������
//��ʼ������
SqQueue* Init_CirQueue()
{
	SqQueue* Q = (SqQueue*)malloc(sizeof(SqQueue));
	if (!Q)
		exit(0);
	Q->front = Q->rear = 0;
	return(Q);
}
//�ж϶����Ƿ�Ϊ��
bool IsEmpty_Queue(SqQueue* Q)
{
	if (Q->front == Q->rear)
		return 1;       /*  ���пգ�����ʧ�ܱ�־  */
	return 0;
}
//�ж϶����Ƿ�����
bool IsFull_Queue(SqQueue* Q)
{
	if ((Q->rear + 1) % MAX_QUEUE_SIZE == Q->front)	/*  ����*/
		return 1;
	return 0;
}
//ͳ�ƶ�����Ԫ�ظ���
int Size_Queue(SqQueue* Q)
{
	return (Q->rear + MAX_QUEUE_SIZE - Q->front) % MAX_QUEUE_SIZE;
}
//�������в���Ԫ��
bool Push(SqQueue* Q, BiTNode e)
/*  ������Ԫ��e���뵽ѭ������Q�Ķ�β  */
{
	if (IsFull_Queue(Q))	/*  ����*/
	{
		printf("Insert: The queue is full.\n");
		return 1;
	}
	Q->array[Q->rear].data = e.data;   /*  Ԫ��e���  */
	Q->array[Q->rear].lChild = e.lChild;
	Q->array[Q->rear].rChild = e.rChild;
	Q->rear = (Q->rear + 1) % MAX_QUEUE_SIZE;
	/*  ��βָ����ǰ�ƶ�  */
	return 0;        /*  ��ӳɹ�    */
}
//ȡ����Ԫ��
bool Pop(SqQueue* Q, BiTNode* x)
/*  ��ѭ������Q�Ķ���Ԫ�س���  */
{
	if (IsEmpty_Queue(Q))	/*  �ӿգ����ش����־    */
	{
		printf("The queue is empty.\n");
		return 1;       /*  ���пգ�����ʧ�ܱ�־  */
	}
	x->data = Q->array[Q->front].data;   /*  ȡջ��Ԫ��  */
	x->lChild = Q->array[Q->front].lChild;
	x->rChild = Q->array[Q->front].rChild;
	Q->front = (Q->front + 1) % MAX_QUEUE_SIZE;
	/*  ����ָ����ǰ�ƶ�  */
	return 0;
}

//���򴴽�������
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
		printf("����%d�����ӽڵ㣺", ch);
		CreateBiTree(&(*T)->lChild);
		printf("����%d�����ӽڵ㣺", ch);
		CreateBiTree(&(*T)->rChild);
	}return 1;
}

//����������ݹ飩
void TraverseBiTree(BiTree T)
{
	if (T == NULL)return;
	printf("%d ", T->data);
	TraverseBiTree(T->lChild);
	TraverseBiTree(T->rChild);
}
//����������ݹ飩
void InOrderBiTree(BiTree T)
{
	//������������
	if (T == nullptr)
		return;
	InOrderBiTree(T->lChild);
	printf("%d ", T->data);
	InOrderBiTree(T->rChild);
}

//����������ݹ飩
void PostOrderBiTree(BiTree T)
{
	//������������
	if (T == nullptr)
		return;
	PostOrderBiTree(T->lChild);
	PostOrderBiTree(T->rChild);
	printf("%d ", T->data);
}
//�����������
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

//���������Ϊ1�Ľ�����
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
 * 1��	ʵ�ֶ�����ǰ�����򡢺�������ĵݹ��㷨��
 * 2��	�������������ȣ��ݹ�ͷǵݹ��㷨����
 * 3��	ͳ�ƶ�������Ϊ1�Ľڵ�������ݹ�ͷǵݹ��㷨����
 *
 */

//������
int main(void)
{
	BiTree T;

	int deepth = -1, num = 0;
	printf("�������һ������ֵ,-1��ʾû�ж�Ӧ����:\n");
	CreateBiTree(&T);
	printf("�������������:\n");
	TraverseBiTree(T);
	printf("\n");
	printf("�������������:\n");
	InOrderBiTree(T);
	printf("\n");
	printf("�������������:\n");
	PostOrderBiTree(T);
	printf("\n");
	deepth = TreeDeep(T);
	printf("�������Ϊ:%d", deepth);
	printf("\n");
	deepth = TreeDeep_norecursion(T);
	printf("�������Ϊ:%d", deepth);
	printf("\n");
	num = Degree1count(T);
	printf("���Ķ�Ϊ1�Ľ�����Ϊ:%d", num);
	printf("\n");
	num = Degree1count_norecursion(T);
	printf("���Ķ�Ϊ1�Ľ�����Ϊ:%d", num);
	printf("\n");
	return 0;
}