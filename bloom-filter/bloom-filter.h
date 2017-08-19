#pragma once

#include <stdio.h>
#include <string>
#include <vector>

class BloomFilter 
{
	static size_t default_bytes_nb;
	static unsigned int default_seeds_nb;
	size_t bytes_nb;
	unsigned int seeds_nb;
	std::vector<unsigned int> seeds;
	char* bitset;

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