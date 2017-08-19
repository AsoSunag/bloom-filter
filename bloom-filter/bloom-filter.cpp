#include "bloom-filter.h"
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include "xxhash.h"

size_t BloomFilter::default_bytes_nb = 100;
unsigned int BloomFilter::default_seeds_nb = 8;

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
	bitset = (char*) calloc (bytes_nb, sizeof(char));
	for (unsigned int i = 0; i < seeds_nb; ++i)
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
		unsigned int hash = XXH64((void*)input.c_str(), input.size(), seed);
		indexes[ind++] = std::pair<unsigned int, unsigned int>{hash % bytes_nb, hash & 0b111};
	});
	std::sort(indexes.begin(), indexes.end());

	std::for_each(indexes.begin(), indexes.end(), [&](std::pair<unsigned int, unsigned int> index)
	{
		probably_exist &= (bitset[index.first] & index.second) != 0;
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
		unsigned int hash = XXH64((void*)input.c_str(), input.size(), seed);
		indexes[ind++] = std::pair<unsigned int, unsigned int>{hash % bytes_nb, hash & 0b111};
	});
	std::sort(indexes.begin(), indexes.end());

	std::for_each(indexes.begin(), indexes.end(), [&](std::pair<unsigned int, unsigned int> index)
	{
		probably_exist &= (bitset[index.first] & index.second) != 0;
		bitset[index.first] = bitset[index.first] | index.second;
	});
	return probably_exist;
}
