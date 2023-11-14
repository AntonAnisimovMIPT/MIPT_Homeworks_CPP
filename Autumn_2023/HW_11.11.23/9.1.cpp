#include <iostream>

class Drawing_API_v1
{
public:

    void draw() const { std::cout << "drawing API v1" << std::endl; }

}; // class Drawing_API_v1 : public Drawing_API

class Drawing_API_v2
{
public:

    void draw() const { std::cout << "drawing API v2" << std::endl; }

}; // class Drawing_API_v2 : public Drawing_API

template <typename Drawing_API>
class Handling
{
public:
    explicit Handling(const Drawing_API & drawing_API) : m_drawing_API(drawing_API) {}

    void draw() const {
        m_drawing_API.draw();
    }

protected:

    const Drawing_API & m_drawing_API;

}; // class Shape



int main()
{

    Handling<Drawing_API_v1>(Drawing_API_v1()).draw();
    Handling<Drawing_API_v2>(Drawing_API_v2()).draw();
    return 0;
}
