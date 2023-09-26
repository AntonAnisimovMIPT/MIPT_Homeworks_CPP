#include <iostream>

void merge(int* a, int left, int middle, int right);

void mergeSort(int* arr, int left, int right){
    if (left + 1 >= right) {
        return;
    }

    auto middle =  left + (right - left) / 2;
    mergeSort(arr, left, middle);
    mergeSort(arr, middle, right);
    merge(arr, left, middle, right);
}

void merge(int* a, int left, int middle, int right) {
    
    const auto size = right - left;
    
    auto tmp = new int[size]{};
    
    const auto begin = left;
    const auto end = middle;
    
    for (auto i = 0; i < size; ++i) {
        
        if (left < end && middle < right && a[left] <= a[middle]) {
            
            tmp[i] = a[left++];
            
        }
        
        else if (left < end && middle < right) {
            
            tmp[i] = a[middle++];
            
        }
        
        else if (left < end) {
            
            tmp[i] = a[left++];
            
        }
        
        else {
            
            tmp[i] = a[middle++];
            
        }
        
    }
    
    for (auto i = 0; i < size; ++i) {
        
        a[begin + i] = tmp[i];
        
    }
    
    delete[] tmp;
}

int main() {
    const auto size = 10;
    auto need_to_sort = new int[size]{};

    std::cout << "Old unsorted array: ";
    for (auto i = size; i > 0; --i) {

        need_to_sort[size - i] = i;

    }
    for (auto i = 0; i < size; ++i) {

        std::cout << need_to_sort[i] << " ";

    }

    mergeSort(need_to_sort, 0, size);

    std::cout << "\nNew sorted array: ";
    for (auto i = 0; i < size; ++i) {

        std::cout << need_to_sort[i] << " ";

    }
}
