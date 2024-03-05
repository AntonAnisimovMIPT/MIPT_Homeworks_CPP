#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <numeric>
#include <chrono>



class StartException : public std::exception {
public:
    const char* what() const noexcept override;
};

class PauseException : public std::exception {
public:
    const char* what() const noexcept override;
};

class MeanException : public std::exception {
public:
    const char* what() const noexcept override;
};



class Timer
{
public:

    using clock_t = std::chrono::steady_clock;

    using time_point_t = clock_t::time_point;

    explicit Timer() :  is_started(false) {}

    double elapsed() const;

    void start();
    void pause();
    void restart();
    double get_mean_measure();
    void print_measurements();

private:

    time_point_t m_begin;

    std::vector<double> m_measurements;

    bool is_started;

};

#endif
