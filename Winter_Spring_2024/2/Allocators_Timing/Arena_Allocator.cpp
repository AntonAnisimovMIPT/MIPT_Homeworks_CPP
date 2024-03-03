#include <Arena_Allocator.h>

	Arena_Allocator::Arena_Allocator(std::size_t size) : m_size(size)
	{
		m_begin = ::operator new(m_size, default_alignment);
	}

	Arena_Allocator::~Arena_Allocator() noexcept
	{
		::operator delete(m_begin, default_alignment);
	}

	[[nodiscard]] void * Arena_Allocator::allocate(std::size_t size, std::size_t alignment)
	{
		void * first = get_byte(m_begin) + m_offset;

		auto space = m_size - m_offset;

		if (first = std::align(alignment, size, first, space); first) // note: modifies first and space
		{
			m_offset = m_size - space + size; 
			
			return first; // note: aligned pointer
		}
		else return nullptr;
	}

	void Arena_Allocator::print() const
	{
		std::cout << m_begin << ": ";

		std::cout << std::setw(4) << std::right << std::setfill('0') << m_offset;

		std::cout << " / " << m_size << std::endl;
	}

	std::byte* Arena_Allocator::get_byte(void* ptr) const noexcept {
    	return std::bit_cast<std::byte*>(ptr);
	}

