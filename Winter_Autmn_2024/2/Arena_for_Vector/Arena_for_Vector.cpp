#include <bit>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

#include <boost/noncopyable.hpp>

template <typename T>
class Arena_Allocator // note: no deallocations for blocks of different sizes
{
public:
	using value_type = T;

	explicit Arena_Allocator(std::size_t size) : m_size(size)
	{
		m_begin = ::operator new(m_size, default_alignment);
	}

	~Arena_Allocator() noexcept
	{
		::operator delete(m_begin, default_alignment);
	}

	[[nodiscard]] T * allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t))
	{

		void * first = get_byte(m_begin) + m_offset;

		auto space = m_size - m_offset;

		if (first = std::align(alignment, size, first, space); first) // note: modifies first and space
		{
			m_offset = m_size - space + size; 
			
			return std::bit_cast<T*>(get_byte(m_begin) + m_offset); // note: aligned pointer
		}
		else return nullptr;
	}

	void deallocate(T* p, std::size_t n) noexcept {}

	void print() const
	{
		std::cout << m_begin << ": ";

		std::cout << std::setw(4) << std::right << std::setfill('0') << m_offset;

		std::cout << " / " << m_size << std::endl;
	}

private:

	std::byte * get_byte(void * ptr) const noexcept
	{
		return std::bit_cast < std::byte * > (ptr);
	}

public:

	static inline const std::align_val_t default_alignment { alignof(std::max_align_t) };

private:
	
	std::size_t m_size   = 0;
	std::size_t m_offset = 0;

	void * m_begin = nullptr;

}; // class Arena_Allocator : private boost::noncopyable


int main()
{
	Arena_Allocator<int> allocator(1024);

    std::vector<int, Arena_Allocator<int>> vec(std::move(allocator));

    vec.push_back(1);
	vec.push_back(11);
    vec.push_back(111);

	for (const auto& elem : vec)
    {
        std::cout << elem << std::endl;
    }

}