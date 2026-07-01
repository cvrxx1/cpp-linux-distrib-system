#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>

using namespace std;

// Сортировка выбором для shared_ptr
template<typename T>
void selectionSort(vector<T>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (*arr[j] < *arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(arr[i], arr[min_idx]);
        }
    }
}

// Бинарный поиск для shared_ptr
template<typename T>
int binarySearch(const vector<T>& arr, const T& target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (*arr[mid] == *target) {
            return mid;
        }
        else if (*arr[mid] < *target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

// Функция для вывода всех дистрибутивов (работает с любыми итераторами)
template<typename IteratorPtr>
void printAllDistros(IteratorPtr beginPtr, IteratorPtr endPtr) {
    int count = 0;
    auto it = *beginPtr;
    auto end = *endPtr;
    
    while (it != end) {
        cout << "  [" << count++ << "] ";
        (*it)->get_info();
        ++it;
    }
}

#endif