#include <Arena_Allocator.h>
#include <Chain_Allocator.h>
#include <Stack_Allocator.h>
#include <timer.h>

auto Time_for_NewDelete(std::size_t size_block, Timer& alloc_timer, Timer& dealloc_timer, int number_iterations) {
    for (size_t i = 0; i < number_iterations; i++)
        {
            alloc_timer.start();
            auto* ptr = ::operator new(size_block);
            alloc_timer.pause();

            dealloc_timer.start();
            ::operator delete(ptr);
            dealloc_timer.pause();
        }


    std::cout<< "Allocation time for ::operator new: " << alloc_timer.get_mean_measure() << "\n"; 
    alloc_timer.restart();

    std::cout<< "Deallocation time for ::operator delete: " << dealloc_timer.get_mean_measure() << "\n"; 
    dealloc_timer.restart();
}


void Comparison_with_Arena(std::size_t size, std::size_t size_block, Timer& alloc_timer, Timer& dealloc_timer, int number_iterations) {
    
    try {
        
        for (int i = 0; i < number_iterations; ++i) {

            alloc_timer.start(); 
            Arena_Allocator allocator(size);
            auto ptr = allocator.allocate(size_block);
            alloc_timer.pause(); 

            dealloc_timer.start();
            dealloc_timer.pause();
            
        }
    std::cout << "Allocation time for Arena: " << alloc_timer.get_mean_measure() << "\n";
    std::cout << "Deallocation time for Arena: " << dealloc_timer.get_mean_measure() << "\n";

    alloc_timer.restart();
    dealloc_timer.restart();

    Time_for_NewDelete(size_block, alloc_timer, dealloc_timer, number_iterations);
    
    }
    catch(const std::exception& exception) {
        std::cout << exception.what() << "\n";
    }
    
}

void Comparison_with_Stack(std::size_t size, std::size_t size_block, Timer& alloc_timer, Timer& dealloc_timer, int number_iterations) {
    
    try {
        
        for (int i = 0; i < number_iterations; ++i) {

            alloc_timer.start(); 
            Stack_Allocator allocator(size);
            auto ptr = allocator.allocate(size_block);
            alloc_timer.pause(); 

            dealloc_timer.start();
            allocator.deallocate(ptr);
            dealloc_timer.pause();

        }
    std::cout << "Allocation time for Stack: " << alloc_timer.get_mean_measure() << "\n";
    std::cout << "Deallocation time for Stack: " << dealloc_timer.get_mean_measure() << "\n";

    alloc_timer.restart();
    dealloc_timer.restart();

    Time_for_NewDelete(size_block, alloc_timer, dealloc_timer, number_iterations);

    }
    catch(const std::exception& exception) {
        std::cout << exception.what() << "\n";
    }

}

void Comparison_with_Chain(std::size_t size, std::size_t size_block, Timer& alloc_timer, Timer& dealloc_timer, int number_iterations) {
    
    try {
        
        for (int i = 0; i < number_iterations; ++i) {

            alloc_timer.start(); 
            Chain_Allocator allocator(size, size_block);
            auto ptr = allocator.allocate();
            alloc_timer.pause(); 

            dealloc_timer.start();
            allocator.deallocate(ptr);
            dealloc_timer.pause();
            
        }
    std::cout << "Allocation time for Chain: " << alloc_timer.get_mean_measure() << "\n";
    std::cout << "Deallocation time for Chain: " << dealloc_timer.get_mean_measure() << "\n";

    alloc_timer.restart();
    dealloc_timer.restart();

    Time_for_NewDelete(size_block, alloc_timer, dealloc_timer, number_iterations);

    }
    catch(const std::exception& exception) {
        std::cout << exception.what() << "\n";
    }
    
}
    
int main() {

    const std::size_t KB = 1024;
    const std::size_t MB = 1024 * KB;
    const std::size_t GB = 1024 * MB;
    Timer alloc_timer;
    Timer dealloc_timer;

    std::cout<< "--Size = 1 KB--";
    std::cout << "\nTests for size_block = 128 bytes:\n";
    Comparison_with_Arena(KB, 128, alloc_timer, dealloc_timer, 100);
    Comparison_with_Stack(KB, 128, alloc_timer, dealloc_timer, 100);
    Comparison_with_Chain(KB, 128, alloc_timer, dealloc_timer, 100);

    std::cout << "\nTests for size_block = 512 bytes:\n";
    Comparison_with_Arena(KB, 128, alloc_timer, dealloc_timer, 100);
    Comparison_with_Stack(KB, 128, alloc_timer, dealloc_timer, 100);
    Comparison_with_Chain(KB, 128, alloc_timer, dealloc_timer, 100);

    std::cout<< "--Size = 1 MB--";
    std::cout << "\nTests for size_block = 128 KB:\n";
    Comparison_with_Arena(MB, 128 * KB, alloc_timer, dealloc_timer, 100);
    Comparison_with_Stack(MB, 128 * KB, alloc_timer, dealloc_timer, 100);
    Comparison_with_Chain(MB, 128 * KB, alloc_timer, dealloc_timer, 100);

    std::cout << "\nTests for size_block = 512 KB:\n";
    Comparison_with_Arena(MB, 512 * KB, alloc_timer, dealloc_timer, 100);
    Comparison_with_Stack(MB, 512 * KB, alloc_timer, dealloc_timer, 100);
    Comparison_with_Chain(MB, 512 * KB, alloc_timer, dealloc_timer, 100);

    std::cout<< "--Size = 1 GB--";
    std::cout << "\nTests for size_block = 128 MB:\n";
    Comparison_with_Arena(GB, 128 * MB, alloc_timer, dealloc_timer, 100);
    Comparison_with_Stack(GB, 128 * MB, alloc_timer, dealloc_timer, 100);
    Comparison_with_Chain(GB, 128 * MB, alloc_timer, dealloc_timer, 100);

    std::cout << "\nTests for size_block = 512 MB:\n";
    Comparison_with_Arena(GB, 512 * MB, alloc_timer, dealloc_timer, 100);
    Comparison_with_Stack(GB, 512 * MB, alloc_timer, dealloc_timer, 100);
    Comparison_with_Chain(GB, 512 * MB, alloc_timer, dealloc_timer, 100);


}