#include <iostream>

class Fahrenheit_Sensor
{
public:

    double get_temperature() const { return 451.0; } // note: old interface

}; // class Fahrenheit_Sensor

class Sensor
{
public:

    virtual ~Sensor() = default;

public:

    virtual double get_temperature() const = 0;

}; // class Sensor

class Adapter : public Sensor, private Fahrenheit_Sensor
{

public:

    double get_temperature() const override // note: the same interface
    {
        return (Fahrenheit_Sensor::get_temperature() - 32.0) * 5.0 / 9.0;
    }


};

int main()
{
    Sensor* p = new Adapter();

    std::cout << p->get_temperature() << "\n";
    delete p;


    return 0;
}