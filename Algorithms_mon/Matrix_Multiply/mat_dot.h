#pragma once
#include <vector>
#include <stdexcept>

using namespace std;

#define ld long double

vector<vector<ld>> mat_dot(const vector<vector<ld>> matA, vector<vector<ld>> matB) {
	size_t rowA = matA.size(), colA = matA[0].size(),
		rowB = matB.size(), colB = matB[0].size();
	if (colA != rowB) throw runtime_error("Incompatible matrix dimensions for multiplication.");
	vector<vector<ld>> PE(rowA, vector<ld>(colB, 0));
	for (size_t t = 0; t < rowA + colA + colB - 1; t++) {
		for (size_t i = 0; i < rowA; i++) {
			for (size_t j = 0; j < colB; j++) {
				size_t k = t - i - j;
				if (k < colB)
					PE[i][j] += matA[i][k] * matB[k][j];
			}
		}
	}
	return PE;
}