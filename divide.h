#pragma once

bool isPrime(int number) {
	int divider = 2;

	int upperBound = int(sqrt(number));

	while (divider <= upperBound) {
		if (number % divider == 0) {
			return false;
		}
		divider++;
	}

	return true;
}

namespace SEQUENTIAL {
	vector<int> primesDivide(int a, int b, bool output = true) {
		Time time;

		vector<int> results;
		results.reserve(b - a + 1);

		for (int i = a; i <= b; i++) {
			if (isPrime(i)) {
				results.push_back(i);
			}
		}

		time.stop();
		if (output) cout << "primesDivide: " << time.get() << endl;

		return results;
	}
}

namespace NAIVE {
	vector<int> PARALLEL_primesDivide(int a, int b, bool output = true) {
		Time time;
		vector<int> results;
		results.reserve(b - a + 1);

#pragma omp parallel
		{
#pragma omp for
			for (int i = a; i <= b; i++) {
				if (isPrime(i)) { 
					results.push_back(i);
				}
			}
		}
		time.stop();

		if (output) cout << "NAIVE PARALLEL_primesDivide: " << time.get() << endl;

		return results;
	}
}

namespace BEST {
	vector<int> PARALLEL_primesDivide(int a, int b, bool output = true) {
		Time time;
		vector<int> results;
		results.reserve(b - a + 1);

		int threadsCount = omp_get_max_threads();
		vector<vector<int>> privateResults(threadsCount, vector<int>());

		for (int i = 0; i < threadsCount; i++) {
			privateResults[i].reserve(b - a + 1);
		}

#pragma omp parallel
		{

#pragma omp for
			for (int i = a; i <= b; i++) {
				if (isPrime(i)) {
					privateResults[omp_get_thread_num()].push_back(i);
				}
			}
		}
		
		for (int i = 0; i < threadsCount; i++) {
			results.insert(results.end(), privateResults[i].begin(), privateResults[i].end());
		}

		time.stop();
		if (output) cout << "BEST PARALLEL_primesDivide: " << time.get() << endl;

		return results;
	}
}