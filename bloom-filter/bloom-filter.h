#pragma once

#include <stdio.h>
#include <string>
#include <vector>

typedef unsigned long long U64;

class BloomFilter 
{
	static size_t default_bytes_nb;
	static size_t default_seeds_nb;
	size_t bytes_nb;
	size_t U64_nb;
	size_t seeds_nb;
	std::vector<U64> seeds;
	U64* bitset;

public:
	BloomFilter();
	BloomFilter(size_t bytes_nb);
	BloomFilter(size_t items_nb, float false_positive_probability);
	~BloomFilter();

	bool Lookup(const std::string& input) const;
	bool Add(const std::string& input);

private:
	void Initialize();
};