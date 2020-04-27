#pragma once

typedef bool CHECK;

vector<int> primesSieve(int a, int b) {
	//Time time;
	int upperBound = int(sqrt(b));
	vector<int> firstPrimes = primesDivide(2, upperBound, false);
	//vector<CHECK> checked(b + 1, false);
	CHECK* checked = new CHECK[b + 1]{ false };

	Time time;
	for (int i = 0; i < firstPrimes.size(); i++) {
		//int multiplicity = a - a%firstPrimes[i];
		int multiplicity = firstPrimes[i] * 2;


		while (multiplicity <= b) {
			checked[multiplicity] = true;

			multiplicity += firstPrimes[i];
		}
	} 	time.stop();
	vector<int> primes;
	primes.reserve(b - a + 1);

	for (int i = a; i <= b; i++) {
		if (!checked[i]) {
			primes.push_back(i);
		}
	}
	//time.stop();
	cout << "primesSieve: " << time.get() << endl;

	delete[] checked;

	return primes;
}