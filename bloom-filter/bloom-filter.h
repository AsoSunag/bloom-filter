#pragma once

#include <stdio.h>
#include <string>
#include <vector>

typedef unsigned long long U64;

class BloomFilter
{
	static size_t default_bytes_nb;
	static size_t default_seeds_nb;
	static std::string default_serialization_path;
	static std::string default_serialization_filename;
	static unsigned int magic_header;
	static unsigned int serialization_version;
	size_t bytes_nb;
	size_t U64_nb;
	size_t seeds_nb;
	std::string serialization_path;
	std::string serialization_filename;
	std::vector<U64> seeds;
	U64* bitset;

public:
	BloomFilter();
	BloomFilter(size_t bytes_nb);
	BloomFilter(size_t items_nb, float false_positive_probability);
	~BloomFilter();

	bool Lookup(const std::string& input) const;
	bool Add(const std::string& input);
	bool Serialize() const;
	bool Unserialize();

	const std::string& GetSerializationPath() const { return serialization_path; }
	void SetSerializationPath(const std::string& path) { serialization_path = path; }
	const std::string& GetSerializationFilename() const { return serialization_filename; }
	void SetSerializationFilename(const std::string& filename) { serialization_filename = filename; }

private:
	void Initialize();
};