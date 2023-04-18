#include <iostream>

using namespace std;

const int MAXN = 500;
int n, m;


class ParTree
{
	int n;
	int* values;
public:
	ParTree(int n)
	{
		this->n = n;
		values = new int[n+1];
		for (int i = 1; i <= n; i++) values[i] = i;
	}

	~ParTree()
	{
		delete[] values;
	}

	int find(int x) {
		if (values[x] == x) return x;
		return values[x] = find(values[x]);
	}

	void Union(int x, int y) {
		values[find(x)] = find(y);
	}

	void print()
	{
		for (int i = 1; i <= n; i++) {
			if (values[i] == i) {
				for (int j = 1; j <= n; j++) {
					if (find(j) == i) cout << j << ' ';
				}
				cout << endl;
			}
		}
	}
};



int main() {
	cin >> n >> m;
	if (n <= 0 || n >= MAXN)
		return -1;
	ParTree* tree = new ParTree(n);
	for (int i = 1; i <= m; i++) {
		int p1, p2;
		cin >> p1 >> p2;
		tree->Union(p1, p2);
	}
	tree->print();

	delete tree;

	return 0;
}
