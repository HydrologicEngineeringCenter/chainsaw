#pragma once
#include <string>
#include <vector>
using namespace std;

class DssDatabase
{
private:
	std::string m_filename;
	long long ifltab[250];
	void m_init();
	
public:
	DssDatabase();
	DssDatabase(std::string filename, int version);
	DssDatabase(string filename);
	~DssDatabase();
	void Catalog();
	void Tabulate(string path, string startDate, string startTime);
	void Info(string path);
	int InsertIrregular(string path, string date, double val);
	void PrintGridToConsole(std::string &path);
	void PrintTimeSeriesToConsole(std::string& path, string startTime, string endTime);
	int ImportShef(string shefFileToImport, string shefParmFile, string sensorFile, string parameterFile);
	int Close();
	static int Squeeze(std::string filename);
	int WriteTs(vector<float> fvalues, string path, string startDate, string startTime, string units, string type);
	
private:
	zStructRecordSize *GetRecordSize(string path);
};


