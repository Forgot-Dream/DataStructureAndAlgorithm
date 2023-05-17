#include <chrono>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

constexpr int MAX_DATA_VALUE = 99999;

int get_random_int(int min, int max) {
    static random_device r;
    static mt19937_64 mt(r());
    uniform_int_distribution<int> distribution(min, max);
    return distribution(mt);
}

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
        array.emplace_back(i + 1);
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

void quick_sort(vector<int>& array, int start, int end, bool count_time = false) {
    if (start >= end)
        return;
    long long start_time;
    if (count_time)
        start_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    //int index = array[start]; // 初始元素
    int index = get_random_int(start,end);
    int left = start, right = end;
    while (left < right) {
        while (array[right] >= index && left < right)
            right--;
        array[left++] = array[right];
        while (array[left] <= index && left < right)
            left++;
        array[right--] = array[left];
    }
    array[left] = index;
    quick_sort(array, start, left - 1);
    quick_sort(array, left + 1, end);
    if (count_time) {
        auto end_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        printf("use %lld ms to sort %d data\n", end_time - start_time, end - start + 1);
    }
}

int main() {
    auto* data_array = new vector<int>();

    int data_size = 100000;

    cout << "随机数据进行顺序排序" << endl; 
    generate_data(*data_array, data_size); //生成随机数据
    //    print_data(*data_array);
    quick_sort(*data_array, 0, data_array->size() - 1, true);
    //    print_data(*data_array);
    data_array->clear();

    /*使用顺序数据可能造成爆栈 需要把预留栈大小扩大*/

    cout << "顺序数据进行顺序排序" << endl;
    generate_order_data(*data_array, data_size); //生成顺序数据
    quick_sort(*data_array, 0, data_array->size() - 1, true);
    data_array->clear();

    cout << "逆序数据进行顺序排序" << endl;
    generate_reverse_order_data(*data_array, data_size);//生成逆序数据
    quick_sort(*data_array, 0, data_array->size() - 1, true);

    delete data_array;
    return 0;
}

