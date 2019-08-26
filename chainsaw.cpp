#include "pch.h"
#include "TestingCenter.h"
#include "DssDatabase.h"
#include "heclib.h"
#include <fstream>
#include "Version.h"
#include "DSSGrid.h"

/*
Program to test dss files across platforms;
Testing is for version 6 and version 7 format of files.

The filename indicates what OS created the File
=================================================
Windowsv6.dss
Windowsv7.dss
Sunv6.dss
Sunv7.dss
Linuxv6.dss
Linuxv7.dss

Different tests are in differnet Paths.
===============================================
/basin/TimeSeries1Test/Flow//1Hour/
/basin/TimeSeries2Test/Flow//1Hour/


program will test create/read/overwrite operations.


*/


void Usage(vector<string> args)  
{
	cout << "chainsaw -- DSS file utility" << endl;
	cout << "Usage: " << endl;
	cout << args[0] << " test version [read] [write]   " << endl;
	cout << args[0] << " dump filename.dss " << endl;
	cout << args[0] << " squeeze filename.dss " << endl;
	cout << args[0] << " catalog filename.dss " << endl;
	cout << args[0] << " tabulate filename.dss path" << endl;
	cout << args[0] << " insert filename.dss path date value" << endl;
	cout << args[0] << " workshop " << endl;
	cout << args[0] << " import-shef file.dss input.shef shefParmFile sensorFile parameterFile  " << endl;
	cout << args[0] << " version" << endl;


	cout << "				 where:  version= 6 or 7" << endl;
	cout << "				 where:  read = read test" << endl;
	cout << "				 where:  write = write test" << endl;

	cout << " Examples:" << endl;
	cout << "               -- test 6 read write  # runs cross-platform tests on dss version 6 (read and write)" << endl;
	cout << "               -- test 7 write  # runs cross-platform tests on version 7 (write)" << endl;
	cout << "               -- test read  # runs cross-platform tests (read)" << endl;
}

bool hasArg(vector<string> args, string arg)
{
	return (std::find(args.begin(), args.end(), arg) != args.end());
}
extern "C" {
	int workbench();

}
int main(int argc, char **argv)
{
 

	vector<string> args(argv, argv + argc);

	if (args[1] == "workshop")
	{
		workbench();
	}

	if (args.size() >= 3 && args[1] == "test")
	{
		TestingCenter c = TestingCenter();
		int version = atoi(args[2].c_str());
		bool read = hasArg(args, "read");
		bool write = hasArg(args, "write");

		c.Run(version, read, write);
	}
	else if (args.size() == 3 && args[1] == "squeeze")
	{
		std::string fn = string(args[2]);
		DssDatabase::Squeeze(fn);
	}
	else if (args.size() == 3 && args[1] == "catalog")
	{
		std::string fn = string(args[2]);
		DssDatabase db = DssDatabase(fn);

		db.Catalog();
	}
	else if (args.size() == 4 && args[1] == "tabulate")
	{  // exe  tabulate sample7.dss //SACRAMENTO/PRECIP-INC/01Jan1877/1Day/OBS/ 
		std::string fn = string(args[2]);
		std::string path = string(args[3]);

		DssDatabase db = DssDatabase(fn);

		db.Tabulate(path,"","");
	}
	else if (args.size() == 6 && args[1] == "insert")
	{  // exe  insert sample7.dss /River/Q//IR-Century/test/  01/01/-10000  123.456 
		std::string fn = string(args[2]);
		std::string path = string(args[3]);
		std::string d = string(args[4]);
		std::string v = string(args[5]);
		DssDatabase db = DssDatabase(fn);

		db.InsertIrregular(path,d,atof(v.c_str()));
	}

	else if (args.size() == 3 && args[1] == "dump" )
	{
		std::string fn = string(args[2]);
		DssDatabase db = DssDatabase(fn);
	}
	else if (args.size() == 2 && args[1] == "version")
	{
		cout << DSS_VERSION << endl;
	}
	else if (args.size() == 7 && args[1] =="import-shef") // file.dss input.shef shefParmFile sensorFile parameterFile
	{
		std::string fn = string(args[2]);
		DssDatabase db = DssDatabase(fn);
		db.ImportShef(args[3], args[4], args[5],args[6]);
	}
	else
		Usage(args);

	


}


