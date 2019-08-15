#include "pch.h"
#include "DssTest.h"
using namespace std;

DssTest::DssTest()
{
}


DssTest::~DssTest()
{
}

///
/// Generate a simple sequence of floating point data
///
///
vector<float> DssTest::Sequence(float start, float inc, int size)
{
	vector<float> rval; 
	float val = start;
	for (size_t i = 0; i < size; i++)
	{
		rval.push_back(val);
		val += inc;
	}


	return rval;
}




