#include <iostream>
#include <vector>
#include <chrono>

struct TestCase 
{
	const std::string name;
	bool (*testFn)();
};

bool SimpleUsageTest();

int main ()
{
	std::vector<TestCase> testCases = {
		{"Simple Usage Test", SimpleUsageTest}
	};

	for (auto test : testCases)
	{
		std::cout<<"Test : "<<test.name<<" => "<< (test.testFn() ? "OK" : "FAIL") <<std::endl;
	}
}