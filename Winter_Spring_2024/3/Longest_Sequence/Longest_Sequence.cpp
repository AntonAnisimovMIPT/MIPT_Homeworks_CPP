#include <iostream>
#include <vector>
#include <algorithm>

auto Longest_Sequence(const std::vector<int>& first, const std::vector<int>& second) {

    std::vector<std::vector<int>> tmp(first.size() + 1, std::vector<int>(second.size() + 1, 0));

    for (int i = 1; i <= first.size(); ++i) {
        for (int j = 1; j <= second.size(); ++j) {

            if (first[i - 1] == second[j - 1]) {

                tmp[i][j] = tmp[i - 1][j - 1] + 1;

            } 
            else {

                tmp[i][j] = std::max(tmp[i - 1][j], tmp[i][j - 1]);

            }
        }
    }

    std::vector<int> res;
    auto i = first.size();
    auto j = second.size();

    while (i > 0 && j > 0) {
        if (first[i - 1] == second[j - 1]) {
            res.push_back(first[i - 1]);
            --i;
            --j;
        } else if (tmp[i - 1][j] > tmp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }
    std::reverse(res.begin(), res.end());

    return res;
}

int main() {
    
    std::vector<int> first = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6};
    std::vector<int> second = {1, 2, 3, 4, 5, 6};

    auto seq = Longest_Sequence(first, second);

    for (size_t i = 0; i < seq.size(); i++)
    {
        std::cout << seq[i] << " ";
    }
    

}
