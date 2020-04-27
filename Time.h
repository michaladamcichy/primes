#pragma once

#include "stdafx.h"

class Time {
public:
	double lastTime;
	bool alreadyStopped = false;

	Time() {
		lastTime = omp_get_wtime();
	}

	void stop() {
		if (alreadyStopped) {
			cout << "\nTIMER FATAL ERROR!\n";
			cout << "\nTIMER FATAL ERROR!\n";
			cout << "\nTIMER FATAL ERROR!\n";
		} else {
			alreadyStopped = true;
			lastTime = omp_get_wtime() - lastTime;
		}
	}

	double get() {
		return lastTime;
	}

};
