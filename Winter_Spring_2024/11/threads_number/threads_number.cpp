#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

void sleepy() {
    std::this_thread::sleep_for(std::chrono::microseconds(1)); 
}

int main() {
    std::vector<std::jthread> threads;
    try {
        while (true) {
            threads.emplace_back(sleepy);
        }
    } catch (...) {
        std::cout << "Number of threads: " << threads.size() << std::endl;
    }

}

// в результате вывелось Number of threads: 16214

/*
На оффициальном сайте Microsoft есть такая информация:
"По умолчанию максимальный размер стека потоков, созданных в собственном процессе IIS, составляет 256 КБ."  https://learn.microsoft.com/ru-ru/troubleshoot/developer/webapps/iis/site-behavior-performance/default-maximum-stack-size-thread
т.о максимальное теоретическое кол-во потоков (4 * 1024 * 1024) / 256 = 16384"
*/