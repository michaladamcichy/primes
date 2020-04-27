#pragma once

typedef bool CHECK;

namespace SEQUENTIAL {
	vector<int> primesSieve(int a, int b) {
		Time time;
		int upperBound = int(sqrt(b));
		vector<int> firstPrimes = SEQUENTIAL::primesDivide(2, upperBound, false);
		
		CHECK* checked = new CHECK[b + 1]{ false };

		for (int i = 0; i < firstPrimes.size(); i++) {
			int multiplicity = firstPrimes[i] * 2;


			while (multiplicity <= b) {
				checked[multiplicity] = true;

				multiplicity += firstPrimes[i];
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
		cout << "primesSieve: " << time.get() << endl;

		delete[] checked;

		return primes;
	}
}