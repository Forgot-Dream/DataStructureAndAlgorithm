#include <iostream>
#include <vector>
using namespace std;

void siftDown(vector<int>& nums, int root, int end) {
    int child = root * 2 + 1;
    while (child <= end) {
        if (child + 1 <= end && nums[child] > nums[child + 1]) {
            child++;
        }
        if (nums[root] > nums[child]) {
            swap(nums[root], nums[child]);
            root = child;
            child = root * 2 + 1;
        }
        else {
            break;
        }
    }
}

void buildHeap(vector<int>& nums) {
    for (int i = nums.size() / 2 - 1; i >= 0; i--) {
        siftDown(nums, i, nums.size() - 1);
    }
}

int main() {
    vector<int> nums;
    int num;
    while (cin>>num)
    {
        nums.push_back(num);
        if (cin.peek() == '\n')
            break;
    }
    buildHeap(nums);
    for (auto num : nums) {
        cout << num << " ";
    }
    return 0;
}