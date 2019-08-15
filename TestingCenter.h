#pragma once
#include "pch.h"
#include "DssTest.h"

using namespace std;

class TestingCenter
{
public:
	TestingCenter();
	static string OsName();
	static int CreateMultiplePathFile(std::string filename, int paths, int records);
	int Run(int version, bool read, bool write);
	int Test(string os, int version, bool read, bool write);
	int CreateFile(string filename, int version);
	void Summary();
	~TestingCenter();
private:
	void Test(int status);
	int _version = 0;
	int testCount = 0;
	int failedCount = 0;
	int passCount = 0;
};

