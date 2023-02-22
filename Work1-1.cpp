#include <iostream>

using namespace std;

void move(int size,char a, char b, char c);

int called_time = 0;

int main()
{
	move(4, 'a', 'b', 'c');
	cout << "use " << called_time << " steps" << endl;
}


void move(int size,char a, char b, char c) {
	called_time++;
	if (size == 1) {
		cout << a << " --> " << c << endl;
		return;
	}
	move(size - 1, a, c, b);
	cout << a << " --> " << c<<endl;
	move(size - 1, b, c, a);
}


/*
汉诺塔算法可以抽象为

先把顶部的n-1个视作一个 "整体" 从a->b 借助c

再把第n个移动到c 

最后借助 a 把 "整体"->c

具体"整体"如何移动假设为已知

根据上文的梳理 可以抽象出一个移动的函数
move(int n,char a,char b,char c)
一共移动n个，从a->b借助c


*/