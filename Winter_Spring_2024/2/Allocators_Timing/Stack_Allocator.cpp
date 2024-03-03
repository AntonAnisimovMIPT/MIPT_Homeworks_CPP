#include "stack_allocator.h"

Stack_Allocator::Stack_Allocator(std::size_t size) : m_size(size)
{
    m_begin = ::operator new(m_size, default_alignment);
}

Stack_Allocator::~Stack_Allocator() noexcept
{
    ::operator delete(m_begin, default_alignment);
}

void * Stack_Allocator::allocate(std::size_t size, std::size_t alignment)
{
    void * first = get_byte(m_begin) + m_offset;

    void * block = get_byte(first) + sizeof(Header);

    auto space = m_size - m_offset - sizeof(Header);

    if (block = std::align(alignment, size, block, space); block)
    {
        auto header = get_header(get_byte(block) - sizeof(Header));

        *header = static_cast < Header > (std::distance(get_byte(first), get_byte(block)));

        m_offset = get_byte(block) - get_byte(m_begin) + size;

        return block;
    }
    else return nullptr;
}

void Stack_Allocator::deallocate(void * ptr) noexcept
{
    auto header = get_header(get_byte(ptr) - sizeof(Header));

    m_offset = get_byte(ptr) - get_byte(m_begin) - *header;
}

void Stack_Allocator::print() const
{
    std::cout << m_begin << ": ";

    std::cout << std::setw(4) << std::right << std::setfill('0') << m_offset;

    std::cout << " / " << m_size << std::endl;
}

std::byte * Stack_Allocator::get_byte(void * ptr) const noexcept
{
    return std::bit_cast < std::byte * > (ptr);
}

Stack_Allocator::Header * Stack_Allocator::get_header(void * ptr) const noexcept
{
    return std::bit_cast < Header * > (ptr);
}
