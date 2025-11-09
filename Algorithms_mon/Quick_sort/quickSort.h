#include <iostream>
#include <vector>

using namespace std;

int lomutoPartition(vector<int> &arr, int low, int high) {
    int pivot = arr[low];
    int i = high;

    for (int j = high; j > low; j--) {
        if (arr[j] > pivot) {
            swap(arr[i], arr[j]);
            i--;
        }
    }
    swap(arr[i], arr[low]);
    return i;
}

void quickSort(vector<int>& vec, int low, int high){
    if(low < high){
        int pivot_index = lomutoPartition(vec, low, high);
        quickSort(vec, low, pivot_index - 1); //right side
        quickSort(vec, pivot_index + 1, high); //left side
    }
}