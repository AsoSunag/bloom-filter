#include <iostream>
#include <vector>
#include <chrono>

struct TestCase 
{
	const std::string name;
	bool (*testFn)();
};

bool SimpleUsageTest();
bool MultipleEntriesTest();

int main ()
{
	std::vector<TestCase> testCases = {
		{"Simple Usage Test", SimpleUsageTest},
		{"Multiple Entries Test", MultipleEntriesTest}
	};

	for (auto test : testCases)
	{
		std::cout<<"Start Test : "<<test.name<<std::endl;
		bool result = test.testFn();
		std::cout<<"End Test : "<<test.name<<" => "<< (result ? "OK" : "FAIL") <<std::endl;
	}
}