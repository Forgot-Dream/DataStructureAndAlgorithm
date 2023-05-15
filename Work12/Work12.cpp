#include <iostream>
#include <vector>
#include <random>

#include <Windows.h>

using namespace std;

constexpr int MAX_DATA_VALUE = 9999;

void generate_data(vector<int>& array, int length) {
	random_device r;
	mt19937_64 mt(r());
	uniform_int_distribution<int> distribution(0, MAX_DATA_VALUE);
	for (int i = 0; i < length; ++i) {
		array.emplace_back(distribution(mt));
	}
}

void generate_order_data(vector<int>& array, int length) {
	for (int i = 0; i < length; ++i) {
		array.emplace_back(i);
	}
}

void generate_reverse_order_data(vector<int>& array, int length) {
	for (int i = 0; i < length; ++i) {
		array.emplace_back(length - i);
	}
}

void print_data(vector<int>& array) {
	for (int i : array) {
		cout << i << " ";
	}
	cout << endl;
}

void shell_sort(vector<int>& array) {
	auto start_time = GetTickCount();
	for (int i = array.size() / 2; i > 0; i /= 2) { //i是分组的间隔
		for (int j = 0; j < i; ++j) { //j是第几个序列
			for (int k = j + i; k < array.size(); k += i) { //排序的主要部分
				int temp = array[k], p = k - i;
				while (p >= 0 && temp > array[p]) {
					array[p + i] = array[p];
					p -= i;
				}
				array[p + i] = temp;
			}
		}
	}
	auto end_time = GetTickCount();
	printf("use %ld ms to sort %zu data\n", end_time - start_time, array.size());
}

int main() {
	auto* data_array = new vector<int>();

	int data_size = 100000;

	cout << "随机数据进行逆序排序" << endl;
	generate_data(*data_array, data_size); //生成随机数据
	//print_data(*data_array);
	shell_sort(*data_array);
	//print_data(*data_array);
	data_array->clear();

	cout << "顺序数据进行逆序排序" << endl;
	generate_order_data(*data_array, data_size); //生成顺序数据
	shell_sort(*data_array);
	data_array->clear();

	cout << "逆序数据进行逆序排序" << endl;
	generate_reverse_order_data(*data_array, data_size);//生成逆序数据
	shell_sort(*data_array);

	delete data_array;
	return 0;
}
