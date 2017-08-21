#include "bloom-filter.h"

bool MultipleEntriesTest()
{
	bool retval = true;

	BloomFilter BF;
	retval &= !BF.Lookup("tested");
	retval &= !BF.Lookup("test");
	retval &= !BF.Lookup("tests");
	retval &= !BF.Add("tested");
	retval &= !BF.Add("test");
	retval &= BF.Add("test");
	retval &= BF.Lookup("tested");
	retval &= BF.Add("tested");
	retval &= !BF.Add("tests");
	retval &= BF.Lookup("tested");
	retval &= BF.Lookup("test");
	retval &= BF.Lookup("tests");

	return retval;
}