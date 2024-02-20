#include <Arena_Allocator.h>
#include <Chain_Allocator.h>
#include <Stack_Allocator.h>
#include <timer.h>

template <typename Allocator>
void Comparison(std::size_t size, std::size_t size_block, Timer& alloc_timer, Timer& dealloc_timer, int number_iterations) {
    
    try {
        
        for (int i = 0; i < number_iterations; ++i) {

            if constexpr (!std::is_same_v<Allocator, Arena_Allocator> && !std::is_same_v<Allocator, Chain_Allocator>)
            {
                alloc_timer.start(); 
                Allocator allocator(size);
                auto ptr = allocator.allocate(size_block);
                alloc_timer.pause(); 

                dealloc_timer.start();
                allocator.deallocate(ptr);
                dealloc_timer.pause();

            }
            else if constexpr(std::is_same_v<Allocator, Chain_Allocator>)
            {
                alloc_timer.start(); 
                Allocator allocator(size, size_block);
                auto ptr = allocator.allocate();
                alloc_timer.pause(); 

                dealloc_timer.start();
                allocator.deallocate(ptr);
                dealloc_timer.pause();
            }
            
            else {
                {alloc_timer.start(); 
                Allocator allocator(size);
                auto ptr = allocator.allocate(size_block);
                alloc_timer.pause(); 

                dealloc_timer.start();}
                dealloc_timer.pause();
            }
            
            
        }
    std::cout << "Allocation time for Allocator: " << alloc_timer.get_mean_measure() << "\n";
    std::cout << "Deallocation time for Allocator: " << dealloc_timer.get_mean_measure() << "\n";

    alloc_timer.restart();
    dealloc_timer.restart();

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
    catch(const std::exception& exception) {
        std::cout << exception.what() << "\n";
    }
    
}

int main() {

    const std::size_t size = 1024;
    const std::size_t size_block_1 = 128;
    const std::size_t size_block_2 = 512;
    Timer alloc_timer;
    Timer dealloc_timer;

    std::cout << "\nTests for size_block_1\n";
    std::cout << "---Arena_Allocator---\n";
    Comparison<Arena_Allocator>(size, size_block_1, alloc_timer, dealloc_timer, 10);

    std::cout << "---Stack_Allocator---\n";
    Comparison<Stack_Allocator>(size, size_block_1, alloc_timer, dealloc_timer, 10);

    std::cout << "---Chain_Allocator---\n";
    Comparison<Chain_Allocator>(size, size_block_1, alloc_timer, dealloc_timer, 10);

    std::cout << "\nTests for size_block_2\n";
    std::cout << "---Arena_Allocator---\n";
    Comparison<Arena_Allocator>(size, size_block_2, alloc_timer, dealloc_timer, 10);

    std::cout << "---Stack_Allocator---\n";
    Comparison<Stack_Allocator>(size, size_block_2, alloc_timer, dealloc_timer, 10);

    std::cout << "---Chain_Allocator---\n";
    Comparison<Chain_Allocator>(size, size_block_2, alloc_timer, dealloc_timer, 10);


}