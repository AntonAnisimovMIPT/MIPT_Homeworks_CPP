#include <cstddef>
#include <array>
#include <limits>
#include <cmath>
#include <iostream>

constexpr std::size_t Log2(std::size_t x) {
    std::size_t result = 0;
    while (x > 1) {
        x /= 2;
        ++result;
    }
    return result;
}

class BuddyAllocator {
    
    public:
		BuddyAllocator(const std::size_t size) : m_Size(size) {
			m_StartAddress = ::operator new(size);
			Init();
    	}

		~BuddyAllocator() {
			::operator delete(m_StartAddress);
			m_StartAddress = nullptr;
		}
		void* Allocate(const std::size_t size, const std::size_t alignment);
		void Deallocate(void* ptr);
		void Reset();

	
    private:
		struct Node
		{
			Node* m_Next;
		};

		struct alignas(std::max_align_t) Header
		{
			std::size_t m_Size;
		};

		static constexpr std::size_t s_Log2Header = Log2(sizeof(Header));
		std::array<Node*, std::numeric_limits<std::size_t>::digits10 - s_Log2Header> m_Buckets = {};
        void Init();

		void* m_StartAddress;
		std::size_t m_Size;
};

void* BuddyAllocator::Allocate(const std::size_t size, const std::size_t alignment)
{
	auto bucket = std::max(static_cast<int>(std::ceil(std::log2(size + sizeof(Header))) - 1 - s_Log2Header), 0);

	if (m_Buckets[bucket] != nullptr)
	{
		auto node = m_Buckets[bucket];
		m_Buckets[bucket] = node->m_Next;
		auto header = std::bit_cast<Header*>(node);
		header->m_Size = static_cast<std::size_t>(std::pow(2, bucket + 1 + s_Log2Header)) | 1;
		auto address = static_cast<void*>(std::bit_cast<std::byte*>(node) + sizeof(Header));
		return address;
	}

	int i{};

	for (i = bucket + 1; i < m_Buckets.size(); ++i)
	{
		if (!m_Buckets[i])
			break;
	}

	if (i == m_Buckets.size())
		return nullptr;

	auto temp = m_Buckets[i];
	m_Buckets[i] = temp->m_Next;

	--i;

	for (; i >= bucket; i--)
	{
		auto node = std::bit_cast<Node*>(std::bit_cast<std::byte*>(temp) + (std::size_t)std::pow(2, i + 1 + s_Log2Header));
		node->m_Next = m_Buckets[i];
		m_Buckets[i] = node;
	}

	auto header = std::bit_cast<Header*>(temp);
	header->m_Size = static_cast<std::size_t>(std::pow(2, i + 2 + s_Log2Header)) | 1;
	auto address = static_cast<void*>(std::bit_cast<std::byte*>(temp) + sizeof(Header));

	return address;
}

void BuddyAllocator::Deallocate(void* ptr)
{
	auto header = std::bit_cast<Header*>(std::bit_cast<std::byte*>(ptr) - sizeof(Header));

	const std::size_t size = header->m_Size & ~(std::size_t)1;
	const std::size_t bucket = static_cast<std::size_t>(std::log2(size)) - 1 - s_Log2Header;

	auto node = std::bit_cast<Node*>(header);

	std::size_t buddyNumber;
	std::byte* buddyAddress;

	buddyNumber = (std::bit_cast<std::byte*>(header) - static_cast<std::byte*>(m_StartAddress)) / size;

	if (buddyNumber % 2 == 0)
		buddyAddress = std::bit_cast<std::byte*>(header) + size;
	else
		buddyAddress = std::bit_cast<std::byte*>(header) - size;

	// Check if buddy is occupied to bale early from searching for it
	if (buddyAddress == (static_cast<std::byte*>(m_StartAddress) + m_Size) || *std::bit_cast<std::size_t*>(buddyAddress) & 1)
	{
		node->m_Next = m_Buckets[bucket];
		m_Buckets[bucket] = node;
	}
	else
	{
		Node* prevBuddy = nullptr;
		auto buddy = std::bit_cast<Node*>(buddyAddress);
		auto context = m_Buckets[bucket];

		// Search the bucket for the buddy and update linked listed
		// This could be improved from O(N) to O(LogN) with RBTree of addresses of nodes
		while (context != buddy && context != nullptr)
		{
			prevBuddy = context;
			context = context->m_Next;
		}

		// If buddy was not found in the bucket it was probably split so we can't merge
		if (context == nullptr)
		{
			node->m_Next = m_Buckets[bucket];
			m_Buckets[bucket] = node;
		}
		else
		{
			if (prevBuddy == nullptr)
			{
				m_Buckets[bucket] = buddy->m_Next;
			}
			else
			{
				prevBuddy->m_Next = buddy->m_Next;
			}

			if (buddyNumber % 2 == 0)
			{
				node->m_Next = m_Buckets[bucket + 1];
				m_Buckets[bucket + 1] = node;
			}
			else
			{
				buddy->m_Next = m_Buckets[bucket + 1];
				m_Buckets[bucket + 1] = buddy;
			}
		}
	}
}

void BuddyAllocator::Reset()
{
	const std::size_t bucket = static_cast<std::size_t>(std::ceil(std::log2(m_Size))) - 1 - s_Log2Header;
	for (std::size_t i = 0; i < bucket; ++i)
	{
		m_Buckets[i] = nullptr;
	}
	Init();
}

void BuddyAllocator::Init()
{
	auto root = std::bit_cast<Node*>(m_StartAddress);
	root->m_Next = nullptr;
	const std::size_t bucket = static_cast<std::size_t>(std::ceil(std::log2(m_Size))) - 1 - s_Log2Header;
	m_Buckets[bucket] = root;
}

int main() {
	BuddyAllocator allocator(1024);
    allocator.Allocate(10000, 4);
    allocator.Allocate(20000, 8);
    allocator.Allocate(30000, 16);
}
