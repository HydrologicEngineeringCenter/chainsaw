#include "pch.h"
#include "TestingCenter.h"
#include "DssDatabase.h"

#include <sys/stat.h>


	TestingCenter::TestingCenter()
	{
	}

 

	string TestingCenter::OsName()
	{
#if defined(_MSC_VER) 
		return string("Windows");
#elif __linux
		return  string("Linux");
#elif __sun
		return string("Solaris");
#else
		return string("unknown");
#endif

	}


	int TestingCenter::Run(int version, bool read, bool write)
	{
		_version = version;
		Test("Windows", version,read,write);
		Test("Linux", version, read, write);
		Test("Solaris", version, read, write);

		Summary();
		
		return 0;
	}

	int SampleText1(const char *filename, const char* path, bool read, bool write);
	extern "C" {
    
	int ts_write_irregular(const char* filename, const char* path, int read, int write);
	int SamplePairedData(const char *filename, const char* path, int read, int write);
	int SamplePairedDataDoubles(const char *filename, const char* path, int read, int write);

	}

// https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
	inline bool file_exists(const std::string& name) {
		struct stat buffer;
		int  rval = 0;
//		printf("\nChecking if file '%s' exists",name.c_str());
		rval = stat(name.c_str(), &buffer); 
//		printf("\nstat = %d",stat);
		return rval ==0;
	}

	int TestingCenter::Test(string os, int version, bool read, bool write)
	{
		string fn = os + "v" + to_string(version)+".dss";
		const char* fnc = fn.c_str();

		// if file does not exist, don't create unless on that OS
		// this enforces a principle that file 'Windows7.dss is created on windows.
		if (os != TestingCenter::OsName() && !file_exists(fn))
		{
			printf("\nskipping file that does not exist: %s", fn.c_str());
			return 0;
		}

		// Create the file with the proper version as a separate step so the routines don't need to know the version
		if (CreateFile(fn, version) != 0)
		{
			printf("\nError: error when creating file %s", fn.c_str());
			return -1;
		}
		
		Test( SampleText1(fnc, "/chainsaw/SampleText1/Message/d/e/f/", read, write));
		Test(ts_write_irregular(fnc, "/chainsaw/ts_write_irregular/Flow//~1Day/ts_write_irregular/", read, write));
		Test(SamplePairedData(fnc, "/chainsaw/SamplePairedData/Stage-Damage///Test/", read, write) );
		Test(SamplePairedDataDoubles(fnc, "/chainsaw/SamplePairedDataDoubles/Stage-Damage///Test/", read, write));


		return 0;
	}
	
	int TestingCenter::CreateFile(string filename, int version)
	{
		int v = zgetFileVersion(filename.c_str());

		if (v >= 6 && v <= 7) // file was previously created.
		{ // version needs to match or we have a problem.
			if (v != version)
			{
				printf("\nERORR: the requested version does not match the file ");
				return -1;
		    }
			else
			{
			  return 0;
			}
		}
		else
		if (v < 0)
		{ // problem such as bad filename, or may not be a valid DSS file...
			return v;
		}
		else
		if (v == 0) // file does not exist.  create it with proper version.
		{
			DssDatabase db = DssDatabase(filename, version);
			db.Close();
			return 0;
		}

		printf("\nError: undefined condition: version = %d", v);
		return -1;

	}

	/*
	Runs a test and tracks statisicts on testing
	*/
	void TestingCenter::Test(int status)
 	{

		testCount++;
		if (status == 0)
			passCount++;
		else
			failedCount++;

	}
	/*
	print summary statistics on testing.
	*/
	void TestingCenter::Summary()
	{
		printf("\n==================================");
		printf("\n run from: %s ", TestingCenter::OsName().c_str());
		printf("\n DSS file version = %d", _version);
		printf("\n  Summary of Testing  ");
		printf("\n==================================");
		printf("\n    %d tests started",testCount);
		printf("\n    %d tests passed", passCount);
		printf("\n    %d tests failed",failedCount);

	}
	

	TestingCenter::~TestingCenter()
	{
	}

	/*
	CreateMultiplePathFile can be used to create a large DSS file
	*/
	int TestingCenter::CreateMultiplePathFile(string filename, int paths, int timeSeriesCount)
	{

		using namespace std;

		long long ifltab[250];
		zStructTimeSeries *tss1;
		vector<float> fvalues;

		int status;

		for (int i = 0; i < timeSeriesCount; i++)
		{
			fvalues.push_back((float)i);
		}


		status = zopen(ifltab, filename.c_str());
		if (status != STATUS_OKAY)
		{
			printf("\nError:  Yikes.. bad news with zopen(%s)", filename.c_str());
			return status;
		}
		for (int i = 0; i < paths; i++)
		{
			printf("\ncalling zstructTsNewRegFloats(...) ");
			string path = "/Basin/Location" + to_string(i);
			path += "/Flow//1Hour/C Test/";
			tss1 = zstructTsNewRegFloats(path.c_str(), &fvalues[0], (int)fvalues.size(),
				"21Jan2001", "1200", "cfs", "Inst-Val");
			status = ztsStore(ifltab, tss1, 0);
			zstructFree(tss1);
			if (status != STATUS_OKAY)
			{
				printf("\nError..");
				return status;
			}
		}
		zclose(ifltab);


		return status;
	}
