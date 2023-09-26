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


void insertSort(int* arr, int left, int right) {
    auto size = right - left;
    for(auto i=1; i < size ; i++) {
        for(auto j=i; j > 0 && arr[j-1] > arr[j]; j--) {
            std::swap(arr[j-1], arr[j]);
        }
    }     
}

void hybridSort(int* arr, int left, int right, int half_size) {
    if (right - left + 1 <= half_size) {
        insertSort(arr, left, right);
    } else {
        if (left + 1 >= right) {
            return;
        }

        auto middle = left + (right - left) / 2;
        mergeSort(arr, left, middle);
        mergeSort(arr, middle, right);
        merge(arr, left, middle, right);
    }
}

int main() {
    const auto size = 10;
    auto need_to_sort = new int[size]{};
    auto half_size = size / 2;

    std::cout << "Old unsorted array: ";
    for (auto i = size; i > 0; --i) {

        need_to_sort[size - i] = i;

    }
    for (auto i = 0; i < size; ++i) {

        std::cout << need_to_sort[i] << " ";

    }

    hybridSort(need_to_sort, 0, size, half_size);

    std::cout << "\nNew sorted array: ";
    for (auto i = 0; i < size; ++i) {

        std::cout << need_to_sort[i] << " ";

    }

}
