#include "chain_allocator.h"

Chain_Allocator::Chain_Allocator(std::size_t size, std::size_t size_block) : m_size(size)
{
    m_size_block = std::max(size_block, sizeof(Block));

    if (m_size % m_size_block != 0)
    {
        throw std::runtime_error("invalid size");
    }

    make_chain(); m_begin = m_head;
}

Chain_Allocator::~Chain_Allocator() noexcept
{
    for (std::size_t i = 0; i < std::size(m_chains); ++i)
    {
        ::operator delete(m_chains[i], default_alignment);
    }
}

void * Chain_Allocator::allocate()
{
    if (m_head == nullptr) // note: current chain has ended
    {
        if (m_offset == std::size(m_chains))
        {
            make_chain();
        }
        else m_head = get_block(m_chains[++m_offset - 1]); // note: switch to next chain
    }

    auto block = m_head;

    if (!block->next) // note: try switch to next block in current chain
    {
        if (auto next  = get_byte(  block               ) + m_size_block; 
                 next != get_byte(m_chains[m_offset - 1]) + m_size)
        {
            m_head = get_block(next); m_head->next = nullptr;
        }
        else m_head = m_head->next; // note: current chain has ended
    }
    else m_head = m_head->next; // note: next after deallocation

    return block;
}

void Chain_Allocator::deallocate(void * ptr) noexcept
{
    auto block = get_block(ptr); 
    
    block->next = m_head; m_head = block; // note: link freed block to previous head
}

void Chain_Allocator::print() const
{
    std::cout << m_head << std::endl;
}

std::byte * Chain_Allocator::get_byte(void * ptr) const noexcept
{
    return std::bit_cast < std::byte * > (ptr);
}

Chain_Allocator::Block * Chain_Allocator::get_block(void * ptr) const noexcept
{ 
    return std::bit_cast < Block * > (ptr); 
}

Chain_Allocator::Block * Chain_Allocator::allocate_blocks() const
{
    auto block = get_block(::operator new(m_size, default_alignment));
    
    block->next = nullptr; return block;
}

void Chain_Allocator::make_chain()
{
    m_head = allocate_blocks(); ++m_offset; m_chains.push_back(m_head);
}
