#pragma once
// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "heclib.h"
void runshefdss_(long long *ifltab, int *unitLog, const char *inputFile, const char *shefParamFile,
	const char *sensorFile, const char *paramFile, int *lstoreAll,
	int *ntotal, int *nsets, int *status,
	size_t leninputFile, size_t lenshefParamFile,
	size_t lensensorFile, size_t lenparamFile);


#ifdef __cplusplus
}

#include <iostream>
#include <vector>
#include <algorithm>
#endif

#endif //PCH_H
