#pragma once

namespace NAIVE {
	vector<int> PARALLEL_primesSieveFunctional(int a, int b) {
		//Time time;
		int upperBound = int(sqrt(b));
		vector<int> firstPrimes = BEST::PARALLEL_primesDivide(2, upperBound, false);

		int threadsCount = omp_get_max_threads();
		//vector<CHECK> checked(b + 1, false);
		CHECK* checked = new CHECK[b + 1]{ false };

		Time time;

#pragma omp parallel
		{

			int privateA = getStart(a, b, omp_get_thread_num(), threadsCount);
			int privateB = getEnd(a, b, omp_get_thread_num(), threadsCount);

			for (int i = 0; i < firstPrimes.size(); i++) {
				int multiplicity = firstPrimes[i] * 2;

				while (multiplicity <= privateB) {
					checked[multiplicity] = true;
					multiplicity += firstPrimes[i];
				}
			}
		}
		time.stop();

		vector<int> primes;
		//primes.reserve(b - a + 1);

		for (int i = a; i <= b; i++) {
			if (!checked[i]) {
				primes.push_back(i);
			}
		}
		//time.stop();
		cout << "PARALLEL_primesSieveFunctional: " << time.get() << endl;

		delete[] checked;

		return primes;
		return vector<int>();
	}
}

namespace BETTER {
	vector<int> PARALLEL_primesSieveFunctional(int a, int b) {
		return vector<int>();
	}
}

namespace BEST {
	vector<int> PARALLEL_primesSieveFunctional(int a, int b) {
		return vector<int>();
	}
}