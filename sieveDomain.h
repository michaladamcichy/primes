#pragma once

namespace NAIVE {
	vector<int> PARALLEL_primesSieveDomain(int a, int b) {
		return vector<int>();
	}
}

namespace BETTER {
	vector<int> PARALLEL_primesSieveDomain(int a, int b) {
		return vector<int>();
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


		/*vector<bool> check1(b + 1, false);
		vector<bool> check2(b + 1, false);
		vector<bool> check3(b + 1, false);
		vector<bool> check4(b + 1, false);
		vector<bool> check5(b + 1, false);
		vector<bool> check6(b + 1, false);
		vector<bool> check7(b + 1, false);
		vector<bool> check8(b + 1, false);
		vector<bool> check9(b + 1, false);
		vector<bool> check10(b + 1, false);
		vector<bool> check11(b + 1, false);
		vector<bool> check12(b + 1, false);*/




		//bool* checked = new bool[(b + 1)]{false};

		Time time;
#pragma omp parallel
		{
#pragma omp for
			for (int i = 0; i < firstPrimes.size(); i++) {
				int multiplicity = firstPrimes[i] * 2;

				while (multiplicity <= b) {
					//(*checked[omp_get_thread_num()])[multiplicity] = true;
					checked[omp_get_thread_num()][multiplicity] = true;
					//checked[multiplicity] = true;
					//privateChecked[multiplicity] = true;

					//switch (omp_get_thread_num()) {
					//case 0: check1[multiplicity] = true; break;
					//case 1: check2[multiplicity] = true; break;
					//case 2: check3[multiplicity] = true; break;
					//case 3: check4[multiplicity] = true; break;
					//case 4: check5[multiplicity] = true; break;
					//case 5: check6[multiplicity] = true; break;
					//case 6: check7[multiplicity] = true; break;
					//case 7: check8[multiplicity] = true; break;
					//case 8: check9[multiplicity] = true; break;
					//case 9:check10[multiplicity] = true; break;
					//case 10:check11[multiplicity] = true; break;
					//case 11:check12[multiplicity] = true; break;
					//default: break;
					//}

					multiplicity += firstPrimes[i];
				}
			}
			//#pragma omp critical
			//{
			//			for (int i = 0; i < b + 1; i++) {
			//				checked[i] = checked[i] | privateChecked[i];
			//			}
			//}
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

		cout << "PARALLEL_primesSieveDomain: " << time.get() << endl;

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