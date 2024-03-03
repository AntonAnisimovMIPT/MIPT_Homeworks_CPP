#ifndef ARENA_ALLOCATOR_H
#define ARENA_ALLOCATOR_H

#include <bit>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <memory>

#include <boost/noncopyable.hpp>

class Arena_Allocator : private boost::noncopyable // note: no deallocations for blocks of different sizes
{
public:

	explicit Arena_Allocator(std::size_t size);

	~Arena_Allocator() noexcept;

	[[nodiscard]] void * allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t));

	void print() const;

private:

	std::byte * get_byte(void * ptr) const noexcept;

public:

	static inline const std::align_val_t default_alignment { alignof(std::max_align_t) };

private:
	
	std::size_t m_size   = 0;
	std::size_t m_offset = 0;

	void * m_begin = nullptr;

}; // class Arena_Allocator : private boost::noncopyable

#endif