#include <iostream>
void Merge(int* inp_arr, int left, int middle, int right);

// Сортировка подмассива с индексами в [left, right)
void SubMergeSort(int* arr, int left, int right){
    if (left + 1 >= right) {
        return;
    }

    auto middle =  (right + left) / 2;
    SubMergeSort(arr, left, middle);
    SubMergeSort(arr, middle, right);
    Merge(arr, left, middle, right);
}

// Решим подзадачу слияния двух массивов
void Merge(int* inp_arr, int left, int middle, int right){
    auto first_iter = 0;
    auto second_iter = 0;
    auto res_arr = new int[right - left]{};

    while (left + first_iter < middle && middle + second_iter < right) {
        if (inp_arr[left + first_iter] < inp_arr[middle + second_iter]) {
            res_arr[first_iter + second_iter] = inp_arr[left + first_iter];
            first_iter += 1;
        }
        else {
            res_arr[first_iter + second_iter] = inp_arr[middle + second_iter];
            second_iter += 1;
        }
    }

    while (left + first_iter < middle) {
        res_arr[first_iter + second_iter] = inp_arr[left + first_iter];
        first_iter += 1;
    }

    while (middle + second_iter < right) {
        res_arr[first_iter + second_iter] = inp_arr[middle + second_iter];
        second_iter += 1;
    }

    for (auto i = 0; i < first_iter + second_iter; i++) {
        inp_arr[left + i] = res_arr[i];
    }
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

    SubMergeSort(need_to_sort, 0, size);

    std::cout << "\nNew sorted array: ";
    for (auto i = 0; i < size; ++i) {

        std::cout << need_to_sort[i] << " ";

    }
}
