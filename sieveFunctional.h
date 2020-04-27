#pragma once

#include <algorithm>

namespace NAIVE {
	vector<int> PARALLEL_primesSieveFunctional(int a, int b) {
		Time time;
		int upperBound = int(sqrt(b));
		vector<int> firstPrimes = BEST::PARALLEL_primesDivide(2, upperBound, false);

		int threadsCount = omp_get_max_threads();

		CHECK* checked = new CHECK[b + 1]{ false };

#pragma omp parallel 
		{
			int privateA = getStart(a, b, omp_get_thread_num(), threadsCount);
			int privateB = getEnd(a, b, omp_get_thread_num(), threadsCount);

			for (int i = 0; i < firstPrimes.size(); i++) {
				int multiplicity = firstPrimes[i] * 2; 
				int expr = ((privateA - firstPrimes[i] * 2) / firstPrimes[i]) * firstPrimes[i];
				if (expr > 0) {
					multiplicity += expr;
				}

				while (multiplicity <= privateB) {
					checked[multiplicity] = true;
					multiplicity += firstPrimes[i];
				}
			}
		}

		vector<int> primes;
		primes.reserve(b - a + 1);

		for (int i = a; i <= b; i++) {
			if (!checked[i]) {
				primes.push_back(i);
			}
		}
		time.stop();
		cout << "NAIVE PARALLEL_primesSieveFunctional: " << time.get() << endl;

		delete[] checked;

		return primes;
	}
}

namespace BETTER {
	vector<int> PARALLEL_primesSieveFunctional(int a, int b) {
		Time time;
		int upperBound = int(sqrt(b));
		vector<int> firstPrimes = BEST::PARALLEL_primesDivide(2, upperBound, false);

		int threadsCount = omp_get_max_threads();
		CHECK** checked = new CHECK * [threadsCount];
		for (int i = 0; i < threadsCount; i++) {
			checked[i] = new CHECK[b + 1]{ false };
		}

#pragma omp parallel
		{
			int privateA = getStart(a, b, omp_get_thread_num(), threadsCount);
			int privateB = getEnd(a, b, omp_get_thread_num(), threadsCount);

			for (int i = 0; i < firstPrimes.size(); i++) {
				int multiplicity = firstPrimes[i] * 2;
				int expr = ((privateA - firstPrimes[i] * 2) / firstPrimes[i]) * firstPrimes[i];
				if (expr > 0) {
					multiplicity += expr;
				}

				while (multiplicity <= privateB) {
					checked[omp_get_thread_num()][multiplicity] = true;
					multiplicity += firstPrimes[i];
				}
			}
		}

		vector<int> primes;
		primes.reserve(b - a + 1);

		for (int i = a; i <= b; i++) {
			int sum = false;
			for (int j = 0; j < threadsCount; j++) {
				sum |= checked[j][i];
			}
			if (!sum) {
				primes.push_back(i);
			}
		}

		time.stop();
		cout << "BETTER PARALLEL_primesSieveFunctional: " << time.get() << endl;

		delete[] checked;

		return primes;
		}
	}
