#include <iostream>

const int MAX_N = 10000;

// Cначала научимся находить длину посл-ти Коллатца, зная значения длин ее подпосл-тей.
int col_length(int n, int* length_data) {

    auto length = 1;
    while (n != 1) {
        if (n <= MAX_N && length_data[n] != 0) {
            length += length_data[n] - 1;
            break;
        }
        
        // вычисление члена по определению послед-ти Коллатца
        n = (n % 2 == 0) ? (n /= 2) : (n = 3 * n + 1);
        
        length++;
    }
    
    // кэшируем
    if (n <= MAX_N) {
        length_data[n] = length;
    }
    
    return length;
}

int main() {
    auto max_length = 0;
    auto initial_value = 0;
    int length_data[MAX_N]{};

    // Итерацией по всем элементам найдем тот, у которого наибольшая длина послед-ти.
    for (auto i = 1; i <= MAX_N; ++i) {
        auto i_length = col_length(i, length_data);
        if (i_length > max_length) {
            max_length = i_length;
            initial_value = i;
        }
    }

    std::cout << "Max length: " << max_length << "\n" << "Initial value: " << initial_value;
}
