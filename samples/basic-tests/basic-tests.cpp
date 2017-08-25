#include <chrono>
#include <iostream>
#include <vector>

struct TestCase
{
	const std::string name;
	bool (*testFn)();

	// minimum running time in milliseconds for a benchmark
	unsigned int bench_time;

	// number of iterations between each time check
	size_t bench_iter;
};

void benchmark(const TestCase& testcase)
{
	using namespace std::chrono;
	size_t iterations = 0;
	size_t intermediate_iterations = 0;

	double time_span = 0.f;

	while (time_span < testcase.bench_time)
	{
		intermediate_iterations = 0;
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		while (intermediate_iterations++ != testcase.bench_iter)
		{
			testcase.testFn();
			iterations++;
		}
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<double, std::milli> intermediate_time_span = t2 - t1;

		time_span += intermediate_time_span.count();
	}
	std::cout << "Time(ms) : " << (time_span / iterations) << " - Total Time(ms) : " << time_span << " - Iterations : " << iterations
											<< std::endl;
}

bool SimpleUsageTest();
bool MultipleEntriesTest();
bool SerializationTest();

int main(int argc, char* argv[])
{
	std::vector<TestCase> testCases = {{"Simple Usage Test", SimpleUsageTest, 2 * 1000, 100000},
		{"Multiple Entries Test", MultipleEntriesTest, 2 * 1000, 100000}, {"Serialization Test", SerializationTest, 2 * 1000, 100000}};

	if (argc > 1 && (strcmp(argv[1], "bench") == 0))
	{
		for (auto test : testCases)
		{
			std::cout << "Start Bench : " << test.name << std::endl;
			benchmark(test);
			std::cout << "End Bench : " << test.name << std::endl;
		}
	}
	else
	{
		for (auto test : testCases)
		{
			std::cout << "Start Test : " << test.name << std::endl;
			bool result = test.testFn();
			std::cout << "End Test : " << test.name << " => " << (result ? "OK" : "FAIL") << std::endl;
		}
	}

	return 1;
}