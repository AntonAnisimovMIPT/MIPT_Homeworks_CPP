#ifndef CHAIN_ALLOCATOR_H
#define CHAIN_ALLOCATOR_H

#include <bit>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#include <boost/noncopyable.hpp>

class Chain_Allocator : private boost::noncopyable // note: deallocations at any position for blocks of fixed sizes
{
private:

    struct Block { Block * next = nullptr; };

public:

    explicit Chain_Allocator(std::size_t size, std::size_t size_block);

    ~Chain_Allocator() noexcept;

    [[nodiscard]] void * allocate();

    void deallocate(void * ptr) noexcept;

    void print() const;

private:

    std::byte * get_byte(void * ptr) const noexcept;

    Block * get_block(void * ptr) const noexcept;

    Block * allocate_blocks() const;

    void make_chain();

public:

    static inline const std::align_val_t default_alignment { alignof(std::max_align_t) };

private:

    std::size_t m_size       = 0;
    std::size_t m_size_block = 0;

    Block * m_head = nullptr;

    std::size_t m_offset = 0;

    std::vector < void * > m_chains;

    void * m_begin = nullptr;
};

#endif
