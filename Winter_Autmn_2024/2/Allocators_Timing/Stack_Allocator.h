#ifndef STACK_ALLOCATOR_H
#define STACK_ALLOCATOR_H

#include <bit>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>

#include <boost/noncopyable.hpp>

class Stack_Allocator : private boost::noncopyable // note: deallocations at end for blocks of different sizes
{
private:

    using Header = std::uint8_t;

public:

    explicit Stack_Allocator(std::size_t size);

    ~Stack_Allocator() noexcept;

    [[nodiscard]] void * allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t));

    void deallocate(void * ptr) noexcept;

    void print() const;

private:

    std::byte * get_byte(void * ptr) const noexcept;

    Header * get_header(void * ptr) const noexcept;

public:

    static inline const std::align_val_t default_alignment { alignof(std::max_align_t) };

private:

    std::size_t m_size   = 0;
    std::size_t m_offset = 0;

    void * m_begin = nullptr;

};

#endif // STACK_ALLOCATOR_H
