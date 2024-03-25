#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <ranges>

int main() {

    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "source vector:\n";
    for (auto i : vec)
    {
        std::cout << i << " ";
    }

    // 1. std::is_sorted
    if (std::ranges::is_sorted(vec.begin(), vec.end(), std::less()))
    {
        std::cout << "\nvec is really sorted in increasing";
    }
    else {
        std::cout << "\nvec wasn't sorted in increasing";
    }
    
    // 2. std::rotate_copy
    std::vector<int> rot_vec(vec.size());
    std::ranges::rotate_copy(vec.cbegin(), vec.cbegin() + 3, vec.cend(), rot_vec.begin());
    std::cout << "\nresult of rotate relative third element:\n";
    for (auto i : rot_vec)
    {
        std::cout << i << " ";
    }

    // 3. std::equal
    auto view1 = vec | std::views::drop(3);
    auto view2 = rot_vec | std::views::take(rot_vec.size() - 3);
    if (std::ranges::equal(view1, view2))
    {
        std::cout << "\nvec without first 3 elements equal rot_vec without last 3 elements";
    }
    else {
        std::cout << "\nvec without first 3 elements doesn't equal rot_vec without last 3 elements";
    }

    // 4. std::partial_sort
    std::vector<int> partial_sorted(vec.begin(), vec.end());
    std::ranges::partial_sort(partial_sorted.begin(), std::next(partial_sorted.begin(), 5), partial_sorted.end(), std::less<>());
    std::cout << "\nresult of partial sorting:\n";
    for (auto i : partial_sorted)
    {
        std::cout << i << " ";
    }

    // 5. std::set_intersection
    std::ranges::sort(vec);
    std::ranges::sort(rot_vec);
    std::vector<int> intersection;
    std::ranges::set_intersection(vec, rot_vec, std::back_inserter(intersection));
    std::cout << "\nintersection of elements of rot_vec and rot_vec: ";
    for (auto i : intersection)
    {
        std::cout << i << " ";
    }

    // 6. std::set_union
    std::vector<int> un;
    std::ranges::set_union(vec, rot_vec, std::back_inserter(un));
    std::cout << "\nunion of elements of vec and rot_vec: ";
    for (auto i : un)
    {
        std::cout << i << " ";
    }

    // 7. std::copy_if
    std::vector<int> copied_with_condition;
    std::ranges::copy_if(vec, std::back_inserter(copied_with_condition), [](auto x){ return x%3 == 0;});
    std::cout << "\ncopied with condition: ";
    for (auto i : copied_with_condition)
    {
        std::cout << i << " ";
    }
    
    // 8. std::set_difference
    std::vector<int> diff;
    std::ranges::set_difference(rot_vec, vec, std::back_inserter(diff));
    std::cout << "\ndifference of elements rot_vec and vec: ";
    for (auto i : diff)
    {
        std::cout << i << " ";
    }

    // 9. std::unique_copy
    std::fill_n(vec.begin(), 10, 1);
    std::vector<int> unique;
    std::ranges::unique_copy(vec, std::back_inserter(unique));
    std::cout << "\nunique in vector of 1: ";
    for (auto i : unique)
    {
        std::cout << i << " ";
    }

    // 10. std::ranges::search_n
    std::ranges::sort(vec);
    std::ranges::sort(rot_vec);
    std::vector<int> symmetric_diff;
    std::ranges::set_symmetric_difference(vec, rot_vec, std::back_inserter(symmetric_diff));
    std::cout << "\nsymmetric difference of vec and rot_vec: ";
    for (auto i : symmetric_diff)
    {
        std::cout << i << " ";
    }
    
}
