#include<stdlib.h>
#include<stdio.h>

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

int main() {
	int a = 15;
	int b = 10;
	swap(a, b);
	printf_s("%d\t%d", a, b);
	return 0;
}