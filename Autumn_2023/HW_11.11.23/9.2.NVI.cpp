#include <iostream>

class Course {
public:

    void Time() {
        std::cout << "needed time (hours): " << calculate() << "\n" ;
    }

private:

    virtual double calculate() const {}

};


class Teormech : public Course {
public:
    Teormech(int mark) : m_mark(mark) {};
private:

    double calculate() const override {

        // учет халявности препода, ската при сдаче дз и учет экзамена
        auto freebie = 1.0; // 1 - не халява, 5 - халява
        auto skat = 0; // 1 - скат дз запрещен, 0 - разрешен
        auto exam = 1; // 1 - есть экзамен, 0 - нет

        return  (m_mark*15 + skat*10)/freebie + 50*exam;

    }

    int m_mark;

};

class Electronics : public Course {
public:
    Electronics(int mark) : m_mark(mark) {}
private:

    double calculate() const override {

        // учет халявности препода и учет экзамена
        auto freebie = 3.0; // 1 - не халява, 5 - халява
        auto exam = 1; // 1 - есть экзамен, 0 - нет

        return  (m_mark*15)/freebie + 50*exam;

    }

    int m_mark;
};


int main() {


    Teormech(5).Time();
    Electronics(6).Time();


    return 0;
}