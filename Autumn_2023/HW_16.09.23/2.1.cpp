#include <iostream>

const int MAX_N = 10000;

// Cначала научимся находить длину посл-ти Коллатца, зная значения длин ее подпосл-тей.
int col_length(int n, int length_data[]) {

    // "База" рекурсии
    if (n == 1) {
        return 1;
    }

    // Та самая ключевая идея кэширования (итоговая длина вычисляется как длина самого элемента (=1) + длина посл-ти, следующей после этого элемента.
    auto length = (n % 2 == 0) ? (1 + col_length(n / 2, length_data)) : (1 + col_length(3 * n + 1, length_data));

    if (n <= MAX_N) {
        length_data[n] = length; // Возможно это условие излишне, т.к итерация в строке 29 автоматом выполняет это условие, но лишняя защита не помешает.
    }

    return length;
}

int main() {
    auto max_length = 0;
    auto initial_value = 0;
    int length_data[MAX_N + 1]{};

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
