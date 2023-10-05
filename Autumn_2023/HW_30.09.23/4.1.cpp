#include <iostream>

class Base
{
public:
    virtual Base* memeber_pointer() {

        Base* b_ptr = new Base;
        return b_ptr;

    }

    void type_output() {

        std::cout << "Base!!!";

    }
};

class Derived : public Base
{
public:
    virtual Derived* memeber_pointer() {

        Derived* d_ptr = new Derived;
        return d_ptr;



    }

    void type_output() {

        std::cout << "Derived";


    }
};

int main()
{
    Derived derived;
    Base *base = &derived;

    std::cout << "overriden return type: ";
    derived.memeber_pointer()->type_output();
    std::cout << ", but return type of base is ";
    base->memeber_pointer()->type_output();



}
