int main() {

    const auto size = 10;
    auto ptr_arr = new int[size]{};

    for (auto i = size; i > 0; --i) {

        ptr_arr[size - i] = i;

    }

    for (auto i = 1 ; i < size; ++i) {
        auto pulled = ptr_arr[i];
        auto j = i - 1;

        while (j >= 0 && ptr_arr[j] > pulled) {
            ptr_arr[j + 1] = ptr_arr[j];
            j--;
        }
        ptr_arr[j + 1] = pulled;
    }
}
