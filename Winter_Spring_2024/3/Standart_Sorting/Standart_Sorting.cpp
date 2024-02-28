#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>

template <typename Container>
auto Aka_std_sort(Container& container) {

    std::vector<std::reference_wrapper<typename Container::value_type>> wrapper;

    // насколько  понял, через обычный оператор [] со списками нельзя работать, а через такой цикл for можно
    for (auto& element : container) {
        wrapper.push_back(std::ref(element));
    }

    std::sort(wrapper.begin(), wrapper.end());

    Container tmp;
    for (size_t i = 0; i < wrapper.size(); i++)
    {
        tmp.push_back(wrapper[i].get());
    }
    
    auto cont_it = container.begin();
    auto tmp_it = tmp.begin();

    while (cont_it != container.end() && tmp_it != tmp.end()) {
        *cont_it = *tmp_it;
        ++cont_it;
        ++tmp_it;
    }  
    
}
int main () {
    std::list<int> lst = {124, 1, 45678, 34, -67890, 100000};
    Aka_std_sort(lst); 

    for (const auto& elem : lst) {
        std::cout << elem << " ";
    }   
}
