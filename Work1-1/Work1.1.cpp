#include <iostream>

using namespace std;

void move(int size, char a, char b, char c);

int called_time = 0;

int main()
{
	move(4, 'a', 'b', 'c');
	cout << "use " << called_time << " steps" << endl;
}


void move(int size, char a, char b, char c) {
	called_time++;
	if (size == 1) {
		cout << a << " --> " << c << endl;
		return;
	}
	move(size - 1, a, c, b);
	cout << a << " --> " << c << endl;
	move(size - 1, b, c, a);
}


/*
��ŵ���㷨���Գ���Ϊ

�ȰѶ�����n-1������һ�� "����" ��a->b ����c

�ٰѵ�n���ƶ���c

������ a �� "����"->c

����"����"����ƶ�����Ϊ��֪

�������ĵ����� ���Գ����һ���ƶ��ĺ���
move(int n,char a,char b,char c)
һ���ƶ�n������a->b����c
*/