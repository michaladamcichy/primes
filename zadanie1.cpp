#include "stdafx.h"
#include "Time.h"

#include "utils.h"
#include "divide.h"
#include "primesSieve.h"
#include "sieveDomain.h"
#include "sieveFunctional.h"

using namespace std;

const bool printResults = false;

int main()
{
	std::cout << "Hello World!\n";

	int maxThreadsCount = omp_get_max_threads();
	int threadsCount = omp_get_num_threads();

	cout << "maxThreadsCount = " << maxThreadsCount << '\n';
	cout << "threadsCount = " << threadsCount << '\n';

	cout << getStart(10, 50, 5, 6) << endl;
	cout << getEnd(10, 50, 4, 6) << endl;


	cout << endl << endl;


	int a = 10, b = 1000000000;

	//results = primesDivide(a, b);
	//print(results);

	//results = PARALLEL_primesDivide(a, b);
	//print(results);

	//while (true) {
	vector<int> results1 = primesSieve(a, b);
	if(printResults)
	print(results1);

	vector<int> results2 = PARALLEL_primesSieveDomain(a, b);
	if (printResults)
	print(results2);

	vector<int> results3 = PARALLEL_primesSieveFunctional(a, b);
	if (printResults)
	print(results3);

	if (!check(results1, results2) || !check(results2, results3)) {
		cout << "\nFATAL ERROR\nFATAL ERROR\nFATAL ERROR\n";
	}

		b *= 10;

		cout << endl << endl;
	//}

	return 0;
}
