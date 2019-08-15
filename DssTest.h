#pragma once
#include "pch.h"
#include "DssDatabase.h"
using namespace std;
class DssTest
{
public:
	DssTest();
	~DssTest();
	static vector<float> Sequence(float start, float inc, int size);
	virtual int Run(DssDatabase db) = 0;


};

