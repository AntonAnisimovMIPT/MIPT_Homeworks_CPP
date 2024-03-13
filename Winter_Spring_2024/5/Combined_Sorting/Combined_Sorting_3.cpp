#include <iostream>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

template <typename Lambda>
void insertion_sort(std::vector < int > & v, std::size_t l, std::size_t r, Lambda comparator) // note: O(N^2) complexity 
{
	for (auto i = l + 1; i < r; ++i)
	{
		for (auto j = i; j > l; --j)
		{
			if (comparator(v[j - 1], v[j]))
			{
				std::swap(v[j], v[j - 1]);
			}
		}
	}
}

template <typename Lambda>
void merge_sort(std::vector < int > & v, std::size_t l, std::size_t m, std::size_t r, Lambda comparator)
{
	const auto begin = l, end = m;

	std::vector < int > t(r - l, 0); // note: one additional container instead of two

	for (auto & e : t) 
	{
		e = v[((l < end && ((m < r && comparator(v[l], v[m])) || (m == r))) ? l++ : m++)];
	}

	for (std::size_t i = 0; i < std::size(t); ++i) v[begin + i] = t[i];
}

template <typename Lambda>
void merge_sort(std::vector < int > & v, std::size_t l, std::size_t r, Lambda comparator) // note: O(N*log(N)) complexity (amortized)
{
	if (static const std::size_t block = 64; r - l <= block)
	{
		insertion_sort(v, l, r, comparator); // good: double nested loop instead of recursive calls
	}
	else
	{
		auto m = std::midpoint(l, r); 
		
		merge_sort(v, l, m   , comparator);
		merge_sort(v,    m, r, comparator);
		merge_sort(v, l, m, r, comparator);
	}
}

int main()
{
	std::cout << "Enter array size: "; std::size_t n{}; std::cin >> n;

	std::vector < int > vector(n, 0);
    auto increasing = [](int a, int b) { return a > b; };
    auto decreasing = [](int a, int b) { return a < b; };

	for (auto value = static_cast < int > (n); auto & element : vector) element = value--;
	std::cout << "original: " << "\n";
	for (auto element : vector) std::cout << element << ' ';

	std::cout << "\nincreasing: " << "\n";
	merge_sort(vector, 0, n, increasing); // good: half-open intervals preferred in C++
	for (auto element : vector) std::cout << element << ' ';

	std::cout << "\ndecreasing: " << "\n";
	merge_sort(vector, 0, n, decreasing);
	for (auto element : vector) std::cout << element << ' ';

	return 0;
}