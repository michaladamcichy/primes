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
	int maxThreadsCount = omp_get_max_threads();
	int threadsCount = omp_get_num_threads();

	cout << "maxThreadsCount = " << maxThreadsCount << '\n';
	cout << "threadsCount = " << threadsCount << '\n';

	cout << endl << endl;

	int a = 10, b = 1000;

	//DIVIDE
	vector<int> results1 = SEQUENTIAL::primesDivide(a, b);

	vector<int> results2 = NAIVE::PARALLEL_primesDivide(a, b);
	if (!check(results2, results1)) {
		cout << "WRONG RESULT\n\n\n";
	}
	vector<int> results4 = BEST::PARALLEL_primesDivide(a, b);
	if (!check(results4, results1)) {
		cout << "WRONG RESULT\n\n\n";
	}
	//SIEVE FUNCTIONAL
	vector<int> results5 = SEQUENTIAL::primesSieve(a, b);
	if (!check(results1, results1)) {
		cout << "WRONG RESULT\n\n\n";
	}
	vector<int> results6 = NAIVE::PARALLEL_primesSieveFunctional(a, b);
	if (!check(results6, results1)) {
		cout << "WRONG RESULT\n\n\n";
	}
	vector<int> results7 = BETTER::PARALLEL_primesSieveFunctional(a, b);
	if (!check(results7, results1)) {
		cout << "WRONG RESULT\n\n\n";
	}

	//SIEVE DOMAIN
	vector<int> results9 = SEQUENTIAL::primesSieve(a, b);
	if (!check(results9, results1)) {
		cout << "WRONG RESULT\n\n\n";
	}
	vector<int> results10 = NAIVE::PARALLEL_primesSieveDomain(a, b);
	if (!check(results10, results1)) {
		cout << "WRONG RESULT\n\n\n";
	}
	vector<int> results12 = BEST::PARALLEL_primesSieveDomain(a, b);
	if (!check(results12, results1)) {
		cout << "WRONG RESULT\n\n\n";
	}

	return 0;
}
