#include "bloom-filter.h"

bool SimpleUsageTest()
{
	bool retval = true;

	BloomFilter BF;
	retval &= !BF.Lookup("tested");
	retval &= !BF.Add("tested");
	retval &= BF.Lookup("tested");
	retval &= BF.Add("tested");

	return retval;
}