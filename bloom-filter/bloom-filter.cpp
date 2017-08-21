#include "bloom-filter.h"
#include <stdlib.h>
#include <cmath>

#include "xxhash.h"

size_t BloomFilter::default_bytes_nb = 120;
size_t BloomFilter::default_seeds_nb = 8;

BloomFilter::BloomFilter()
	: bytes_nb(default_bytes_nb)
	, seeds_nb(default_seeds_nb)
{
	Initialize();
}

BloomFilter::BloomFilter(size_t bytes_nb)
	: bytes_nb(bytes_nb)
	, seeds_nb(default_seeds_nb)
{
	Initialize();
}

BloomFilter::BloomFilter(size_t items_nb, float false_positive_probability)
{
	size_t bits = (size_t)(-(items_nb * std::log(false_positive_probability))/(std::pow(std::log(2), 2)));
    bytes_nb = std::ceil(bits / 8);
    seeds_nb = (unsigned int)((items_nb / bits) * std::log(2));

    Initialize();
}

void BloomFilter::Initialize()
{
	U64_nb = (size_t)std::ceil(bytes_nb / 8);
	bitset = (U64*) calloc (std::ceil(bytes_nb / 8), sizeof(U64));
	for (size_t i = 0; i < seeds_nb; ++i)
	{
		seeds.push_back(rand());
	}
}

BloomFilter::~BloomFilter()
{
	free(bitset);
}

bool BloomFilter::Lookup(const std::string& input) const
{
	std::vector<std::pair<unsigned int, unsigned int>> indexes(seeds_nb);
	unsigned int ind = 0;
	bool probably_exist = true;

	std::for_each(seeds.begin(), seeds.end(), [&](unsigned int seed)
	{
		U64 hash = XXH64((void*)input.c_str(), input.size(), seed);
		indexes[ind++] = std::pair<unsigned int, unsigned int>{hash % U64_nb, (hash & 0b1111111) | 1};
	});
	std::sort(indexes.begin(), indexes.end());

	std::for_each(indexes.begin(), indexes.end(), [&](std::pair<unsigned int, unsigned int> index)
	{
		probably_exist &= (((bitset[index.first] >> index.second) & 1) != 0);
	});
	return probably_exist;
}

bool BloomFilter::Add(const std::string& input)
{
	std::vector<std::pair<unsigned int, unsigned int>> indexes(seeds_nb);
	unsigned int ind = 0;
	bool probably_exist = true;

	std::for_each(seeds.begin(), seeds.end(), [&](unsigned int seed)
	{
		U64 hash = XXH64((void*)input.c_str(), input.size(), seed);
		indexes[ind++] = std::pair<unsigned int, unsigned int>{hash % U64_nb, (hash & 0b1111111) | 1};
	});
	std::sort(indexes.begin(), indexes.end());

	std::for_each(indexes.begin(), indexes.end(), [&](std::pair<unsigned int, unsigned int> index)
	{
		probably_exist &= (((bitset[index.first] >> index.second) & 1) != 0);
		bitset[index.first] |= ((U64)1 << index.second);
	});
	return probably_exist;
}
