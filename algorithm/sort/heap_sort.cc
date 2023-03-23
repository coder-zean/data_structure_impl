#pragma once
#include <vector>
#include <iostream>

using namespace std;

void MaxHeapify(vector<int>& arr, int start, int end) {
    int last_non_leaf_index = (end - start) / 2 - 1;
    for (int i = last_non_leaf_index; i >= 0; i--) {
        int j = i;
        int left = j * 2 + 1;
        int right = j * 2 + 2;
        while (left < end) {
            if (right < end) {
                if (arr[j] > max(arr[left], arr[right]))  break;
                if (arr[left] > arr[right]) {
                    swap(arr[j], arr[left]);
                    j = left;
                    left = j * 2 + 1;
                    right = left + 1;
                } else {
                    swap(arr[j], arr[right]);
                    j = right;
                    left = j * 2 + 1;
                    right = left + 1;
                }
            } else {
                if (arr[j] > arr[left])  break;
                swap(arr[j], arr[left]);
                j = left;
                left = j * 2 + 1;
                right = left + 1;
            }
        }
    } 
}

void HeapSort(vector<int>& arr) {
    for (int i = arr.size(); i > 0; i--) {
        MaxHeapify(arr, 0, i);
        swap(arr[0], arr[i - 1]);
    }
}

int main() {
    vector<int> arr = { 3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6 };
    HeapSort(arr);
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << ' ';
    cout << endl;
    return 0;
}