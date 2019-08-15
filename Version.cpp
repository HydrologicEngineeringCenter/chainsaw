#include "pch.h"
#include "Version.h"
#include <fstream>

using namespace std;

Version::Version()
{
	// get major, minor, and build
	getFields();
}

void Version::updateVersion(std::string newNum)
{
	// get all fields
	getFields(newNum);

	// overwrite version_build.h
	cout << "#define VERSION_MAJOR " << major << endl;
	cout << "#define VERSION_MINOR " << minor << endl;
	cout << "#define VERSION_REVISION " << build << endl;
	cout << "#define VERSION_BUILD " << patch << endl;
}

void Version::getFields() 
{
	// major
	major = getMajor();
	//minor
	minor = getMinor();
	//build
	build = getBuild();
}

void Version::getFields(string newNum)
{
	// major
	major = getMajor();
	//minor
	minor = getMinor();
	//build
	build = getBuild();
	//patch
	patch = atoi(newNum.c_str());
}

Version::~Version()
{

}

void Version::printVersion()
{
	cout << getMajor() << "." << getMinor() << "." << getBuild() << endl;
}

int Version::getMajor()
{
	string version = DSS_VERSION;
	int dashIndex = version.find("-");
	// major
	string majorStr = version.substr(0, dashIndex);
	int tempMajor = atoi(majorStr.c_str());
	return tempMajor;
}

int Version::getMinor()
{
	string version = DSS_VERSION;
	int dashIndex = version.find("-");
	//minor
	string minorStr = version.substr(dashIndex + 1);
	const char* minorChar = minorStr.c_str();
	int tempMinor = getVersFromChar(*minorChar);
	return tempMinor;
}

int Version::getBuild()
{
	string version = DSS_VERSION;
	int dashIndex = version.find("-");
	//build
	string buildStr = version.substr(dashIndex + 2);
	const char* buildChar = buildStr.c_str();
	int tempBuild = getVersFromChar(*buildChar);
	return tempBuild;
}

int Version::getPatch()
{
	string version = DSS_VERSION;
	int dashIndex = version.find("-");
	//minor
	string minorStr = version.substr(dashIndex + 1);
	const char* minorChar = minorStr.c_str();
	int tempMinor = getVersFromChar(*minorChar);
	return tempMinor;
}

