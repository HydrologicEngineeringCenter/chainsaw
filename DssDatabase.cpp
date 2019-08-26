#include "pch.h"
#include "DssDatabase.h"
#include <fstream>
#include <sstream>
#include <string>
#include "DSSGrid.h"

DssDatabase::DssDatabase()
{
	m_init();
}

void DssDatabase::m_init()
{
	for (int i = 0; i < 250; i++)
	{
		ifltab[i] = 0;
	}
}

DssDatabase::DssDatabase(string filename)
{
	m_init();

	int status = 0;
	m_filename = filename;
	 status = zopen(ifltab, filename.c_str());
	if (status != 0)
	{
		string msg = "Error opening" + filename;
		cout << msg << endl;
		throw new std::exception();
	}
}


DssDatabase::DssDatabase(string filename, int version)
{
	m_init();

	int status = 0;
	m_filename = filename;
	if (version == 6)
		status = zopen6(ifltab, filename.c_str());
	else
		status = zopen7(ifltab, filename.c_str());
	if (status != 0)
	{
		string msg = "Error opening" + filename;
		cout<< msg <<endl;
		throw new std::exception();
	}
}



DssDatabase::~DssDatabase()
{
}

void DssDatabase::Catalog()
{
	std::string line;
	zcatalogFile(ifltab, "c:\\temp\\catlog_temp{010}.txt", 1, "");
	std::ifstream f("c:\\temp\\catlog_temp{010}.txt");
	while (getline(f, line))
	{
		cout << line << endl;
	}
}

void DssDatabase::Tabulate(string path,string startDate, string startTime)
{

	zStructRecordSize *rs = zstructRecordSizeNew(path.c_str());

	int status = zgetRecordSize(ifltab, rs);
	if (status != 0)
	{
		cout << "Error:  Could not find path:'" << path << "'"<< endl;
		return;
	}

	cout << "dataType = " << rs->dataType << endl;

		if ((rs->dataType >= DATA_TYPE_RTS) && (rs->dataType < DATA_TYPE_PD))
		{ // time series
			PrintTimeSeriesToConsole(path);
		}
		if ((rs->dataType >= DATA_TYPE_UGT) && (rs->dataType < DATA_TYPE_SG))
		{
			PrintGridToConsole(path);
		}

		zstructFree(rs);
}

int DssDatabase::InsertIrregular(string path, string date, double val)
{
	double dvalues[1];
	int itimes[1];
	int status = -1;
	dvalues[0] = val;
	int timeGranularitySeconds = MINUTE_GRANULARITY;
	zStructTimeSeries *tss1 = zstructTsNew(path.c_str());
	status = ztsRetrieve(ifltab, tss1, 0, 1, 0);
	if (status == 0)
	{ // use existing granularity
		timeGranularitySeconds = tss1->timeGranularitySeconds;
	}
	zstructFree(tss1);

	zStructTimeSeries *tss = zstructTsNewIrregDoubles(path.c_str(), dvalues, 1, itimes, timeGranularitySeconds, "", "", "INST-VAL");

	itimes[0] = dateToJulian(date.c_str());
	if (itimes[0] != UNDEFINED_TIME)
	{
		tss->times = itimes;
		tss->doubleValues = dvalues;

		int storageFlag_merge = 0; // adding new data
		status = ztsStore(ifltab, tss, storageFlag_merge);
	}
	zstructFree(tss);
	return status;
}

void DssDatabase::PrintGridToConsole(std::string &path)
{

	zStructSpatialGrid *gridStruct = zstructSpatialGridNew(path.c_str());
	DSSGrid::RetrieveGriddedData(ifltab, gridStruct, true);

	//int status = zspatialGridRetrieve(ifltab, gridStruct, 1);
	printGridStruct(ifltab, -1, gridStruct);
	if (gridStruct->_data)
	{
		float*x = (float*)gridStruct->_data;
		size_t size = gridStruct->_numberOfCellsX*gridStruct->_numberOfCellsY;
		cout << "---begin GRID DATA--- " << endl;
		for (size_t i = 0; i < size; i++)
		{
			cout << x[i] << " ";
			if (i > 100)
			{
				cout << " ... " << endl;
				break;
			}
		}
		cout << endl << "---end GRID DATA--- " << endl;
		zstructFree(gridStruct);
	}
}

void DssDatabase::PrintTimeSeriesToConsole(std::string &path)
{

	//zStructTimeSeries *tss = zstructTsNewTimes(path.c_str(), startDate.c_str(), startTime.c_str(), "", "");
	//zStructTimeSeries *tss = zstructTsNewTimes(path.c_str(), "01Jan1877", "0100", "31Dec1878", "2400");
	zStructTimeSeries *tss = zstructTsNewTimes(path.c_str(), "", "", "", "");

	tss->numberValues = 9000;
	int retrieveDoublesFlag = 1; // 0 for as stored  ,  1 for floats,  2 for doubles.
	int boolRetrieveQualityNotes = 0;
	int retrieveFlag = 0;// -2; //
	int status = ztsRetrieve(ifltab, tss, retrieveFlag, retrieveDoublesFlag, boolRetrieveQualityNotes);
	//int status = ztsRetrieve(ifltab, tss, -1, 1, 0);

	if (status != STATUS_OKAY)
	{
		cout << "Erorr reading data" << endl;
		return;
	}

	char cdate[13], ctime[10];
	//int valueTime = tss->startTimeSeconds;

	bool isFloat = tss->floatValues != 0;
	bool foundData = false;

	for (int i = 0; i < tss->numberValues; i++) {
		double val = 0;
		bool missing = false;
		getDateAndTime(tss->times[i], tss->timeGranularitySeconds, tss->julianBaseDate,
			cdate, sizeof(cdate), ctime, sizeof(ctime));
		if (isFloat)
		{
			val = tss->floatValues[i];
			if (val == zmissingFlagFloat())
				missing = true;
		}
		else
		{
			val = tss->doubleValues[i];
			if (val == zmissingFlagDouble())
				missing = true;
		}

		if (missing && !foundData)
			continue;

		if (missing)
			printf("%s %s, \n", cdate, ctime);
		else
		{
			printf("%s %s, %f\n", cdate, ctime, val);
			foundData = true;
		}


		//valueTime += tss->timeIntervalSeconds;
	}
}



int DssDatabase::ImportShef(string shefFileToImport, string shefParmFile, string sensorFile, string parameterFile )
{
	int storeAll = 1;
	int  unitLog =8;
	int ntotal=0;
	int nsets =0;
	int status =0;
//	string logFile = "debug.txt";
	char log[] = "debug.txt";
	fortranopen_(&unitLog, log, strlen(log));
	runshefdss_(&ifltab[0], &unitLog, shefFileToImport.c_str(), shefParmFile.c_str(),
		sensorFile.c_str(), parameterFile.c_str(), &storeAll,
		&ntotal, &nsets, &status,
		strlen(shefFileToImport.c_str()), strlen(shefParmFile.c_str()),
		strlen(sensorFile.c_str()), strlen(parameterFile.c_str()) );

	return status;
}


int DssDatabase::Close()
{
	return zclose(ifltab);
}

int DssDatabase::Squeeze(std::string filename)
{
	int status = zsqueeze(filename.c_str());
	return status;

}

int DssDatabase::WriteTs(vector<float> fvalues, string path,string startDate,string startTime, string units, string type)
{
	zStructTimeSeries *tss1;
//	const char* pathname, float *floatValues, int numberValues,
//		const char *startDate, const char *startTime, const char *units, const char *type)
//{
	tss1 = zstructTsNewRegFloats(path.c_str(), fvalues.data(), (int)fvalues.size(), startDate.data(), startTime.c_str(), units.data(), type.data());
	int status = ztsStore(ifltab, tss1, 0);
	zstructFree(tss1);
	 return status;

}
 
