#include <omp.h>
#include <iostream>

using namespace std;

const long long BIG_NUMBER= 1000000000;

void zad1(long long num_steps = BIG_NUMBER) {
	printf("\nZAD1----------\n");
	double realStart, realStop;
	double x, pi, sum = 0.0;
	int i;
	double step = 1. / (double) num_steps;
	
	realStart = omp_get_wtime();
	for (i = 0; i < num_steps; i++)
	{
		x = (i + .5) * step;
		sum = sum + 4.0 / (1. + x * x);
	}

	pi = sum * step;

	realStop = omp_get_wtime();

	printf("Wartosc liczby PI wynosi %15.12f\n", pi);
	printf("[omp_get_wtime()] %f sekund\n", ((realStop - realStart)));
	printf("\n------------------------------\n");
}

void zad2() {
	printf("\nZAD2----------\n");
	
	double realStart, realStop;
	
	long long num_steps = BIG_NUMBER;
	double x, pi = 0.0, sum = 0.0;
	int i;
	double step = 1. / (double) num_steps;


	realStart = omp_get_wtime();
	#pragma omp parallel
	{
	#pragma omp for
		for (i = 0; i < num_steps; i++) {
			x = (i + .5) * step;
			sum += 4.0 / (1. + x * x);
		}
	}

	pi = sum * step;

	realStop = omp_get_wtime();

	printf("Wartosc liczby PI wynosi %15.12f\n", pi);
	printf("[omp_get_wtime()] %f sekund\n", ((realStop - realStart)));
	printf("\n------------------------------\n");

}

void zad3() {
	printf("\nZAD3----------\n");

	double realStart, realStop;

	long long num_steps = BIG_NUMBER;
	double x, pi = 0.0, sum = 0.0;
	int i;
	double step = 1. / (double)num_steps;


	realStart = omp_get_wtime();
#pragma omp parallel
	{
#pragma omp for
		for (i = 0; i < num_steps; i++) {
			x = (i + .5) * step;
#pragma omp atomic
			sum += 4.0 / (1. + x * x);
		}
	}


	pi = sum * step;

	realStop = omp_get_wtime();

	printf("Wartosc liczby PI wynosi %15.12f\n", pi);
	printf("[omp_get_wtime()] %f sekund\n", ((realStop - realStart)));
	printf("\n------------------------------\n");

}

void zad4() {
	printf("\nZAD4----------\n");

	double realStart, realStop;

	long long num_steps = BIG_NUMBER;
	double x, pi = 0.0, sum = 0.0;
	int i;
	double step = 1. / (double)num_steps;


	realStart = omp_get_wtime();
#pragma omp parallel
	{
		double privateSum = 0.0;
		double x = 0.0;
#pragma omp for
		for (i = 0; i < num_steps; i++) {
			x = (i + .5) * step;
			privateSum += 4.0 / (1. + x * x);
		}

#pragma omp atomic
		sum += privateSum;
	}


	pi = sum * step;

	realStop = omp_get_wtime();

	printf("Wartosc liczby PI wynosi %15.12f\n", pi);
	printf("[omp_get_wtime()] %f sekund\n", ((realStop - realStart)));
	printf("\n------------------------------\n");

}

void zad5() {
	printf("\nZAD5----------\n");

	double realStart, realStop;

	long long num_steps = BIG_NUMBER;
	double x, pi = 0.0, sum = 0.0;
	int i;
	double step = 1. / (double)num_steps;


	realStart = omp_get_wtime();
#pragma omp parallel
	{
		double x = 0.0;
#pragma omp for reduction(+:sum)
		for (i = 0; i < num_steps; i++) {
			x = (i + .5) * step;
			sum += 4.0 / (1. + x * x);
		}
	}


	pi = sum * step;

	realStop = omp_get_wtime();

	printf("Wartosc liczby PI wynosi %15.12f\n", pi);
	printf("[omp_get_wtime()] %f sekund\n", ((realStop - realStart)));
	printf("\n------------------------------\n");

}

void zad6() {
	printf("\nZAD6----------\n");

	double realStart, realStop;

	long long num_steps = BIG_NUMBER;
	double x, pi = 0.0, sum = 0.0;
	int i;
	double step = 1. / (double)num_steps;
	volatile double tab[6] = { 0 };

	realStart = omp_get_wtime();
#pragma omp parallel
	{
		double x = 0.0;
		int id = omp_get_thread_num();
#pragma omp for
		for (i = 0; i < num_steps; i++) {
			x = (i + .5) * step;
			tab[id] += 4.0 / (1. + x * x);
		}

#pragma omp atomic
		sum += tab[id];
	}


	pi = sum * step;

	realStop = omp_get_wtime();


	printf("Wartosc liczby PI wynosi %15.12f\n", pi);
	printf("[omp_get_wtime()] %f sekund\n", ((realStop - realStart)));
	printf("\n------------------------------\n");

}

void zad7() {
	printf("\nZAD7----------\n");

	omp_set_num_threads(2);

	double realStart, realStop;

	long long num_steps = BIG_NUMBER;
	double x, pi = 0.0, sum = 0.0;
	int i;
	double step = 1. / (double)num_steps;
	volatile double tab[50] = { 0 };


	for (int k = 0; k < 50 - 1; k++) {
		realStart = omp_get_wtime();
#pragma omp parallel
		{
			int id = omp_get_thread_num();
			tab[k + id] = 0;
			printf("%d\n", id);
			double x = 0.0;

			for (i = 0; i < num_steps; i++) {
				x = (i + .5) * step;
				tab[k + id] += 4.0 / (1. + x * x);
			}
		}
		realStop = omp_get_wtime();

		printf("[omp_get_wtime()] %f sekund\n", ((realStop - realStart)));
		printf("Wartosc liczby PI wynosi %15.12f\n", tab[k] * step);
		printf("Wartosc liczby PI wynosi %15.12f\n", tab[k + 1] * step);
		printf("\n------------------------------\n");
	}
}

int main()
{
	std::cout << "Hello World!\n";

	int maxThreadsCount = omp_get_max_threads();
	int threadsCount = omp_get_num_threads();

	cout << "maxThreadsCount = " << maxThreadsCount << '\n';
	cout << "threadsCount = " << threadsCount << '\n';

	zad1();
	//zad2();
	//zad3();
	zad4();
	zad5();
	zad6();
	//zad7();
	return 0;
}
