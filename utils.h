#pragma once

void print(vector<int> v) {
	for (auto& el : v) {
		cout << '\n' << el;
	}
}

bool check(vector<int> v1, vector<int> v2) {
	if (v1.size() != v2.size()) {
		return false;
	}
	else {
		for (int i = 0; i < v1.size(); i++) {
			if (v1[i] != v2[i]) {
				return false;
			}
		}
		return true;
	}
}
