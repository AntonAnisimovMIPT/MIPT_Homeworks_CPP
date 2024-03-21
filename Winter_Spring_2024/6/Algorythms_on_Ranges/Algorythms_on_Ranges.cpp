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
    auto range1 = vec | std::views::drop(3);
    auto range2 = rot_vec | std::views::take(rot_vec.size() - 3);
    if (std::ranges::equal(range1, range2))
    {
        std::cout << "\nvec without first 3 elements equal rot_vec without last 3 elements";
    }
    else {
        std::cout << "\nvec without first 3 elements doesn't equal rot_vec without last 3 elements";
    }

    // 4. std::partition
    // здесь почему-то не получается использовать ranges
    auto even = [](int x){return x%2 == 0; };
    auto beggining_of_odd = std::partition(rot_vec.begin(), rot_vec.end(), even);
    std::cout << "\neven elements of rot_vec: ";
    for (auto iter = rot_vec.begin(); iter != beggining_of_odd; ++iter)
    {
        std::cout << *iter << ' ';
    }
    std::cout << "\nodd elements of rot_vec: ";
    for (auto iter = beggining_of_odd; iter != rot_vec.end(); ++iter)
    {
        std::cout << *iter << ' ';
    }

    // 5. std::set_intersection
    std::ranges::sort(rot_vec.begin(), beggining_of_odd);
    std::ranges::sort(beggining_of_odd, rot_vec.end());
    std::vector<int> intersaction;
    std::ranges::set_intersection(rot_vec.begin(), beggining_of_odd, beggining_of_odd, rot_vec.end(), std::back_inserter(intersaction));
    std::cout << "\nintersection of even and odd elements of rot_vec: ";
    for (auto i : intersaction)
    {
        std::cout << i << " ";
    }

    // 6. std::set_union
    std::ranges::sort(rot_vec.begin(), beggining_of_odd);
    std::ranges::sort(beggining_of_odd, rot_vec.end());
    std::vector<int> un;
    std::ranges::set_union(rot_vec.begin(), beggining_of_odd, beggining_of_odd, rot_vec.end(), std::back_inserter(un));
    std::cout << "\nunion of even and odd elements of rot_vec: ";
    for (auto i : un)
    {
        std::cout << i << " ";
    }

    // 7. std::copy_if
    std::vector<int> copied_with_condition;
    std::ranges::copy_if(vec.cbegin(), vec.cend(), std::back_inserter(copied_with_condition), [](int x){ return x%3 == 0;});
    std::cout << "\ncopied with condition: ";
    for (auto i : copied_with_condition)
    {
        std::cout << i << " ";
    }
    
    // 8. std::set_difference
    std::ranges::sort(rot_vec.begin(), rot_vec.end());
    std::ranges::sort(vec.begin(), vec.end());
    std::vector<int> diff;
    std::ranges::set_union(rot_vec.begin(), rot_vec.end(), vec.begin(), vec.end(), std::back_inserter(diff));
    std::cout << "\ndifference of elements in destroyed rot_vec and vec: ";
    for (auto i : diff)
    {
        std::cout << i << " ";
    }

    // 9. std::unique_copy
    std::fill_n(vec.begin(), 10, 1);
    std::vector<int> unique;
    std::ranges::unique_copy(vec.begin(), vec.end(), std::back_inserter(unique));
    std::cout << "\nunique in vectror of 1: ";
    for (auto i : unique)
    {
        std::cout << i << " ";
    }

    // 10. std::exclusive_scan
    // насколько я понял, у этой функции нет ::ranges
    std::vector<int> scan(vec.size());
    std::exclusive_scan(vec.begin(), vec.end(), scan.begin(), 0);
    std::cout << "\nexclusive_scan: ";
    for (auto i : scan)
    {
        std::cout << i << " ";
    }
    
}