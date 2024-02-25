#include <iostream>
#include <timer.h>

void Timing (std::size_t size_chunk, Timer& alloc_timer, Timer& dealloc_timer, int number_iterations) {

    try {
        for (size_t i = 0; i < number_iterations; i++)
        {
            alloc_timer.start();
            auto ptr = ::operator new(size_chunk);
            alloc_timer.pause();

            dealloc_timer.start();
            ::operator delete(ptr);
            dealloc_timer.pause();
        }


        std::cout<< "allocation time for this memory chunk: " << alloc_timer.get_mean_measure() << "\n"; 
        alloc_timer.restart();

        std::cout<< "deallocation time for this memory chunk: " << dealloc_timer.get_mean_measure() << "\n"; 
        dealloc_timer.restart();

    }

    catch(const std::exception& exception) {
        std::cout << exception.what();

    }

}



int main() {
    const std::size_t KB = 1024;
    const std::size_t MB = KB * 1024;
    const std::size_t GB = MB * 1024;

    Timer allocTimer;
    Timer deallocTimer;

    std::cout<<"1 KB:\n";
    Timing(KB, allocTimer, deallocTimer, 100);

    std::cout<<"250 KB:\n";
    Timing(250 * KB, allocTimer, deallocTimer, 100);

    std::cout<<"500 KB:\n";
    Timing(500 * KB, allocTimer, deallocTimer, 100);

    std::cout<<"750 KB:\n";
    Timing(750 * KB, allocTimer, deallocTimer, 100);

    std::cout<<"1 MB:\n";
    Timing(MB, allocTimer, deallocTimer, 100);

    std::cout<<"250 MB:\n";
    Timing(250 * MB, allocTimer, deallocTimer, 100);

    std::cout<<"500 MB:\n";
    Timing(500 * MB, allocTimer, deallocTimer, 100);

    std::cout<<"750 MB:\n";
    Timing(750 * MB, allocTimer, deallocTimer, 100);

    std::cout<<"1 GB:\n";
    Timing(GB, allocTimer, deallocTimer, 100);

    
}