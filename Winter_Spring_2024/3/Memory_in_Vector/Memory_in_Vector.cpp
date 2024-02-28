#include <vector>
#include <iostream>
#include <stdexcept>

int main() {

    std::vector<int> vec1(0);
    const std::size_t size = 17;

    for (std::size_t i = 0; i < size; i++)
    {
        std::cout << "\nsize = " << vec1.size() << "   capacity = " << vec1.capacity();
        vec1.push_back(0);
    }

    /*
        ответ на первый подвопрос: на моей архитектуре, если не хватает емкости для размещения новых эелементов,
        то размер вектора увеличивается в 2 раза.
    */ 
    std::cout << "\n --- \n";



    std::vector<int> vec2;
    vec2.resize(2);
    std::cout << "\nsize = " << vec2.size() << "   capacity = " << vec2.capacity();
    vec2.resize(100);
    std::cout << "\nsize = " << vec2.size() << "   capacity = " << vec2.capacity();
    vec2.resize(3);
    std::cout << "\nsize = " << vec2.size() << "   capacity = " << vec2.capacity();

    /*
        ответ на второй вопрос: если значения resize <= значению capacity, то capacity не изменяется,
        но если значение resize > значения capacity, то capacity увеличивается в такое кол-во раз, чтобы быть равным значению size.
    */

    std::cout << "\n --- \n";    

    std::vector<int> v3;
    std::cout << "max_size = " << v3.max_size() << "\n";
    const std::size_t more_than_max_size = v3.max_size() + 1;
    try
    {
        v3.resize(more_than_max_size);
    }
    catch(const std::length_error& e)
    {
        std::cerr << "Failed to allocate memory: " << e.what() << '\n';
    }

    /*
        Ответ на третий подвопрос: если пытаемся выделить размер, который больше, чем максимально допустимый, 
        то возникает исключение std::length_error.
    */
    



    
    


}