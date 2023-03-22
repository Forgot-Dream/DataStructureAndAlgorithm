#include<iostream>
#include<string.h>

using namespace std;


int* findNext(string p) {
	/*�����㷨����ģʽ�������һ��next[]����ÿһλ��ʾӦ����ת�����±�*/
	/*�Ż��㷨����aaaaax����ַ����������ؼ���Ӧ����-1 0 1 2 3 4��
	������Ȼ���±�Ϊ4ʱʧ�����ת3������3��ΪҲ��a�����Ա�Ȼ����ʧ�䣬������ǿ����Ż���[-1, -1, -1, -1, -1, 4]
	�ڴ˹����У�����Ҳ��Ӧ��kmp���㷨˼�룬ģʽ��ͬʱ��Ϊ������ģʽ��*/
	int i = 0;
	int k = -1;
	int m = p.length();
	int* next = new int[m];
	next[0] = -1;
	while (i < m) {
		//i�ǵ���ָ�룬k��ģʽ��ָ��
		i++; //����3����� 1)ʧ���i��λ��k��-1�ӵ�0(��K����)  2)ǰһ��ƥ��ɹ����������һλ 3)��һ�ν���ѭ��ʱ���Ե�һ��Ԫ�أ��ӵڶ���Ԫ�ؿ�ʼƥ��
		k++;

		if (i == m) //i���ﾡͷ���˳�
			break;

		if (p[i] == p[k]) //ǰһλƥ�����������һλ����ƥ����ϣ�˵�����ٲ���ģʽ��ƥ��ģ����Կ���**����**ǰ���next�����ֵ
			next[i] = next[k];
		else //ʧ���k����Ӧ����ת�����±�
			next[i] = k;

		while (k >= 0 && p[i] != p[k])//��whileѭ������ʧ�������������ʧ�����ת������ٴη���ʧ�����ٴ���ת�������Ƿ���ͷ����Ҳ����-1
			k = next[k];//kһֱ��ת��next������ָӦ����ת���±�

		/*
		abcabcx
		   abcabcx

	    abcaabca b c
		    abca a bcabc
		�ڴ˴�����ʧ�䣬Ȼ��ģʽ���ƶ�
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
	/*KMP�㷨ƥ��ģʽ�ַ���*/
	string P, T;
	cout << "����������";
	cin >> T;
	cout << "������ģʽ��";
	cin >> P;
	int* next = findNext(P);

	cout << KMP(T, P, next);

	delete[] next;

	return 0;
}
