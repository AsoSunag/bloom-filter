#include "bloom-filter.h"

bool SerializationTest()
{
	bool retval = true;

	BloomFilter* BF1 = new BloomFilter();
	retval &= !BF1->Add("tested");
	retval &= !BF1->Add("test");
	retval &= BF1->Lookup("tested");
	retval &= BF1->Lookup("test");
	retval &= !BF1->Lookup("notest");
	BF1->SetSerializationPath("bin/");
	retval &= BF1->Serialize();
	delete BF1;

	BloomFilter* BF2 = new BloomFilter();
	BF2->SetSerializationPath("bin/");
	retval &= BF2->Unserialize();
	retval &= BF2->Add("tested");
	retval &= BF2->Add("test");
	retval &= !BF2->Add("tests");
	retval &= BF2->Lookup("tested");
	retval &= BF2->Lookup("test");
	retval &= !BF2->Lookup("notest");
	delete BF2;

	return retval;
}