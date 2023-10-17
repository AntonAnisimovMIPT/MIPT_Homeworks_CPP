#include <iostream>

template <typename T>
class Container {
public:

    Container() : m_data(nullptr), m_capacity(0)
    {
        std::cout << "default constructor" << "\n";
    }

    explicit Container(int capacity) : m_capacity(capacity)
    {
        std::cout << "main constructor" << "\n";

        m_data = new T[m_capacity]{};
    }

    Container(const Container & other) : m_capacity(other.m_capacity)
    {
        std::cout << "copy constructor" << "\n";

        m_data = new T[m_capacity];

        for (auto i = 0; i < m_capacity; ++i)
        {
            m_data[i] = other.m_data[i];
        }
    }


    Container(Container && other) noexcept : Container()
    {
        std::cout << "move constructor" << "\n";

        swap(other);
    }

    Container & operator=(Container other)
    {
        std::cout << "copy and swap" << "\n";

        swap(other);

        return *this;
    }

    void swap(Container & other)
    {
        std::swap(m_data, other.m_data);
        std::swap(m_capacity, other.m_capacity);
    }

    ~Container()
    {
        std::cout << "destructor" << "\n";

        if (m_data)
        {
            delete[] m_data;
        }
    }

    [[nodiscard]] const T& front() const {
        if (!empty()) {

            return m_data[0];

        }
        else {

            std::cout << "size = 0!!!" << "\n";

        }
    }

    T& front() {
        if (!empty()) {

            return m_data[0];

        }
        else {

            std::cout << "size = 0!!!" << "\n";

        }
    }

    [[nodiscard]] const T& back() const {

        if(!empty()) {

            return m_data[m_size - 1];

        }

        else {

            std::cout << "size = 0!!!" << "\n";

        }

    }

    T& back() {

        if(!empty()) {

            return m_data[m_size - 1];

        }

        else {

            std::cout << "size = 0!!!" << "\n";

        }

    }

    [[nodiscard]] bool empty() const {

        return m_size == 0;

    }

    T& operator[] (int i) {

        if (i < m_size) {

            return m_data[i];

        }

        else {

            std:: cout << "the entered index is greater than the number of elements in the array!!!" << "\n";

        }

    }

    const T& operator[] (int i) const {

        if (i < m_size) {

            return m_data[i];

        }

        else {

            std:: cout << "the entered index is greater than the number of elements in the array!!!" << "\n";

        }

    }

    [[nodiscard]] int Get_Size() const {

        return m_size;

    }

    [[nodiscard]] int Get_Capacity() const {

        return m_capacity;

    }

    void clear() {

        Container().swap(*this);

    }

    void push_back(const int value) {

        if (m_size >= m_capacity) {

            int new_capacity = (m_capacity == 0 ? 1 : 2 * m_capacity);
            T* new_data = new T[new_capacity];
            for (auto i = 0; i < m_size; ++i) {

                new_data[i] = m_data[i];

            }

            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;

        }

        m_data[m_size++] = value;

    }

private:

    T* m_data;
    int m_size{};
    int m_capacity{};

};



int main()
{

    const int capacity = 3;
    Container<char> vect = Container<char>(capacity);


    vect.push_back('a');
    vect.push_back('b');
    vect.push_back('c');


    std::cout << "empty/not empty: ";
    (vect.empty() ? (std::cout << "empty") : (std::cout << "not empty"));
    std::cout << "\n";


    std::cout << "elements of vector: ";
    for (auto i = 0; i < vect.Get_Size(); ++i) {

        std::cout << vect[i] << " ";

    }
    std::cout << "\n";

    std::cout << "front: " << vect.front() << "\n";
    std::cout << "back: " << vect.back() << "\n";

    vect.front() = 'd';
    vect.back() = 'e';
    std::cout << "new front: " << vect.front() << "\n";
    std::cout << "new back: " << vect.back() << "\n";

    vect.push_back('r');

    std::cout << "size: " << vect.Get_Size() << "\n";
    std::cout << "capacity: " << vect.Get_Capacity() << "\n";











    return 0;
}