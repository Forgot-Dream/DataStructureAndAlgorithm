#include<iostream>
#include<string.h>

using namespace std;


int* findNext(string p) {
	/*朴素算法：从模式串计算出一个next[]，其每一位表示应该跳转到的下标*/
	/*优化算法：如aaaaax这个字符串，按朴素计算应该是-1 0 1 2 3 4，
	但是显然在下标为4时失配会跳转3，但是3因为也是a，所以必然发生失配，因此我们可以优化成[-1, -1, -1, -1, -1, 4]
	在此过程中，我们也能应用kmp的算法思想，模式串同时作为主串和模式串*/
	int i = 0;
	int k = -1;
	int m = p.length();
	int* next = new int[m];
	next[0] = -1;
	while (i < m) {
		//i是单向指针，k是模式串指针
		i++; //处理3种情况 1)失配后，i进位，k从-1加到0(即K归零)  2)前一次匹配成功后再往后进一位 3)第一次进入循环时忽略第一个元素，从第二个元素开始匹配
		k++;

		if (i == m) //i到达尽头后退出
			break;

		if (p[i] == p[k]) //前一位匹配后，如果往后进一位还能匹配的上，说明至少部分模式是匹配的，所以可以**复用**前面的next数组的值
			next[i] = next[k];
		else //失配后，k就是应该跳转到的下标
			next[i] = k;

		while (k >= 0 && p[i] != p[k])//此while循环处理失配后的情况：发生失配后跳转，如果再次发生失配则再次跳转，最坏情况是返回头部，也就是-1
			k = next[k];//k一直跳转到next数组所指应该跳转的下标

		/*
		abcabcx
		   abcabcx

	    abcaabca b c
		    abca a bcabc
		在此处发生失配，然后模式串移动
		abcabca b c
		      a b caabcabc
		*/
	}

	for (int i = 0; i < m; i++)
	{
		cout << '\t' << next[i];
	}
	cout << endl;
	return next;
}

int KMP(const string& T, const string& P, int* N) {
	int i = 0, j = 0, pLen = P.length(), tLen = T.length();

	if (tLen < pLen)
		return -1;

	while (i < pLen && j < tLen) {
		if (i == -1 || T[j] == P[i])
			i++, j++;
		else
			i = N[i];
	}

	if (i >= pLen)
		return j - pLen;
	else
		return -1;
}

int main() {
	/*KMP算法匹配模式字符串*/
	string P, T;
	cout << "请输入主串";
	cin >> T;
	cout << "请输入模式串";
	cin >> P;
	int* next = findNext(P);

	cout << KMP(T, P, next);

	delete[] next;

	return 0;
}
