#pragma once

namespace NAIVE {
	vector<int> PARALLEL_primesSieveDomain(int a, int b) {
		Time time;
		int upperBound = int(sqrt(b));
		vector<int> firstPrimes = BEST::PARALLEL_primesDivide(2, upperBound, false);

		CHECK* checked = new CHECK[b + 1]{ false };

#pragma omp parallel
		{
#pragma omp for
			for (int i = 0; i < firstPrimes.size(); i++) {
				int multiplicity = firstPrimes[i] * 2;

				while (multiplicity <= b) {
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

		cout << "NAIVE PARALLEL_primesSieveDomain: " << time.get() << endl;

		delete[] checked;

		return primes;
	}
}

namespace BEST {
	vector<int> PARALLEL_primesSieveDomain(int a, int b) {
		//Time time;
		int upperBound = int(sqrt(b));
		vector<int> firstPrimes = BEST::PARALLEL_primesDivide(2, upperBound, false);

		int threadsCount = omp_get_max_threads();

		//vector<vector<CHECK>> checked(threadsCount, vector<CHECK>((b + 1), false));
		CHECK** checked = new CHECK * [threadsCount];
		for (int i = 0; i < threadsCount; i++) {
			checked[i] = new CHECK[b + 1]{ false };
		}

		//bool* checked = new bool[(b + 1)]{false};

		Time time;
#pragma omp parallel
		{
#pragma omp for schedule(dynamic)
			for (int i = 0; i < firstPrimes.size(); i++) {
				int multiplicity = firstPrimes[i] * 2;

				while (multiplicity <= b) {
					//(*checked[omp_get_thread_num()])[multiplicity] = true;
					checked[omp_get_thread_num()][multiplicity] = true;
					//checked[multiplicity] = true;
					//privateChecked[multiplicity] = true;

					multiplicity += firstPrimes[i];
				}
			}
		}
		time.stop();

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

		//time.stop();

		cout << "BEST PARALLEL_primesSieveDomain: " << time.get() << endl;

		delete[] checked;

		return primes;
	}
}


int getStart(int a, int b, int threadIndex, int threadsCount) {
	return a + (b - a) / threadsCount * threadIndex;
}

int getEnd(int a, int b, int threadIndex, int threadsCount) {
	if (threadIndex < threadsCount - 1) {
		return getStart(a, b, threadIndex, threadsCount) + (b - a) / threadsCount - 1;
	}
	else {
		return b;
	}
}