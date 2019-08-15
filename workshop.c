#include <stdio.h>
#include "heclib.h"
#include <string.h>

#define __size 10000


int RequestTimeArray()
{
  long long ifltab[250];
  zStructTimeSeries *tss1;
  int status, i;
	memset(ifltab, 0, sizeof(ifltab));
	status = zopen(ifltab, "sample7.dss");
	if (status != STATUS_OKAY) return status;

	tss1 = zstructTsNew("//SACRAMENTO/TEMP-MIN/01Jan1877/1Day/OBS/"); 

	int trimDataGenerateTimes = -1;
	int returnDoubles = 2;
	status = ztsRetrieve(ifltab, tss1, trimDataGenerateTimes, returnDoubles, 0);

	printf("\nstartJulianDate %d", tss1->startJulianDate);
	printf("\nendJulianDate %d", tss1->endJulianDate);
	printf("\ntimeGranularitySeconds %d", tss1->timeGranularitySeconds);
	printf("\ntimeIntervalSeconds %d", tss1->timeIntervalSeconds);
	printf("\ntimeOffsetSeconds %d", tss1->timeOffsetSeconds);
	printf("\njulianBaseDate %d", tss1->julianBaseDate);


	if (status != 0)
		return status;

	printf("\ntimes     value");
	for (i = 0; i < tss1->numberValues; i++)
	{
		printf("\n%d  %f", tss1->times[i], tss1->doubleValues[i]);
		if (i > 10)
			break;
	}
	zstructFree(tss1);
	return status;
}

int extendedDates()
{
	int count = 142;
	double vals[142];
	int times[142];
	times[0] = -4346384;  vals[0] = 575000;  /* 1/1/-10000 January 1, -10000 */
	times[1] = -4346383;  vals[1] = 575000;  /* 1/2/-10000 January 2, -10000 */
	times[2] = -3615898;  vals[2] = 275000;  /* 1/2/-8000 January 2, -8000 */
	times[3] = -977750;  vals[3] = 190000;  /* 1/3/-777 January 3, -777 */
	times[4] = -694321;  vals[4] = 325000;  /* 1/4/-001 January 4, -001 */
	times[5] = -693589;  vals[5] = 230000;  /* 1/5/001 January 5, 0001 */
	times[6] = -675692;  vals[6] = 150000;  /* 1/6/050 January 6, 0050 */
	times[7] = -420022;  vals[7] = 300000;  /* 1/7/750 January 7, 0750 */
	times[8] = -237399;  vals[8] = 203000;  /* 1/8/1250 January 8, 1250 */
	times[9] = -6778;  vals[9] = 156700;  /* 6/10/1881 June 10, 1881 */
	times[10] = -6403;  vals[10] = 144000;  /* 6/20/1882 June 20, 1882 */
	times[11] = -4958;  vals[11] = 119700;  /* 6/4/1886 June 4, 1886 */
	times[12] = -4570;  vals[12] = 168400;  /* 6/27/1887 June 27, 1887 */
	times[13] = -4206;  vals[13] = 181000;  /* 6/25/1888 June 25, 1888 */
	times[14] = -3106;  vals[14] = 133300;  /* 6/30/1891 June 30, 1891 */
	times[15] = -2733;  vals[15] = 151800;  /* 7/7/1892 July 7, 1892 */
	times[16] = -2386;  vals[16] = 121700;  /* 6/19/1893 June 19, 1893 */
	times[17] = -2027;  vals[17] = 154700;  /* 6/13/1894 June 13, 1894 */
	times[18] = -1286;  vals[18] = 124600;  /* 6/23/1896 June 23, 1896 */
	times[19] = -549;  vals[19] = 159900;  /* 6/30/1898 June 30, 1898 */
	times[20] = -252;  vals[20] = 137900;  /* 4/23/1899 April 23, 1899 */
	times[21] = 168;  vals[21] = 116900;  /* 6/17/1900 June 17, 1900 */
	times[22] = 537;  vals[22] = 144900;  /* 6/21/1901 June 21, 1901 */
	times[23] = 893;  vals[23] = 93600;  /* 6/12/1902 June 12, 1902 */
	times[24] = 1286;  vals[24] = 106200;  /* 7/10/1903 July 10, 1903 */
	times[25] = 1622;  vals[25] = 126900;  /* 6/10/1904 June 10, 1904 */
	times[26] = 2014;  vals[26] = 191100;  /* 7/7/1905 July 7, 1905 */
	times[27] = 2358;  vals[27] = 183800;  /* 6/16/1906 June 16, 1906 */
	times[28] = 2725;  vals[28] = 148600;  /* 6/18/1907 June 18, 1907 */
	times[29] = 3096;  vals[29] = 196000;  /* 6/23/1908 June 23, 1908 */
	times[30] = 3453;  vals[30] = 199300;  /* 6/15/1909 June 15, 1909 */
	times[31] = 3831;  vals[31] = 92000;  /* 6/28/1910 June 28, 1910 */
	times[32] = 4198;  vals[32] = 117800;  /* 6/30/1911 June 30, 1911 */
	times[33] = 4574;  vals[33] = 159900;  /* 7/10/1912 July 10, 1912 */
	times[34] = 4906;  vals[34] = 124700;  /* 6/7/1913 June 7, 1913 */
	times[35] = 5277;  vals[35] = 128800;  /* 6/13/1914 June 13, 1914 */
	times[36] = 5677;  vals[36] = 153200;  /* 7/18/1915 July 18, 1915 */
	times[37] = 6035;  vals[37] = 150600;  /* 7/10/1916 July 10, 1916 */
	times[38] = 6389;  vals[38] = 142400;  /* 6/29/1917 June 29, 1917 */
	times[39] = 6756;  vals[39] = 181900;  /* 7/1/1918 July 1, 1918 */
	times[40] = 7101;  vals[40] = 65100;  /* 6/11/1919 June 11, 1919 */
	times[41] = 7441;  vals[41] = 191500;  /* 5/16/1920 May 16, 1920 */
	times[42] = 7849;  vals[42] = 187000;  /* 6/28/1921 June 28, 1921 */
	times[43] = 8210;  vals[43] = 143900;  /* 6/24/1922 June 24, 1922 */
	times[44] = 8561;  vals[44] = 144000;  /* 6/10/1923 June 10, 1923 */
	times[45] = 8938;  vals[45] = 126400;  /* 6/21/1924 June 21, 1924 */
	times[46] = 9293;  vals[46] = 167400;  /* 6/11/1925 June 11, 1925 */
	times[47] = 9650;  vals[47] = 102800;  /* 6/3/1926 June 3, 1926 */
	times[48] = 10033;  vals[48] = 218900;  /* 6/21/1927 June 21, 1927 */
	times[49] = 10382;  vals[49] = 164900;  /* 6/4/1928 June 4, 1928 */
	times[50] = 10753;  vals[50] = 131900;  /* 6/10/1929 June 10, 1929 */
	times[51] = 11123;  vals[51] = 77700;  /* 6/15/1930 June 15, 1930 */
	times[52] = 11487;  vals[52] = 74400;  /* 6/14/1931 June 14, 1931 */
	times[53] = 11852;  vals[53] = 134700;  /* 6/13/1932 June 13, 1932 */
	times[54] = 12225;  vals[54] = 127100;  /* 6/21/1933 June 21, 1933 */
	times[55] = 12587;  vals[55] = 64300;  /* 6/18/1934 June 18, 1934 */
	times[56] = 12977;  vals[56] = 130200;  /* 7/13/1935 July 13, 1935 */
	times[57] = 13307;  vals[57] = 89700;  /* 6/7/1936 June 7, 1936 */
	times[58] = 13683;  vals[58] = 110700;  /* 6/18/1937 June 18, 1937 */
	times[59] = 14068;  vals[59] = 146000;  /* 7/8/1938 July 8, 1938 */
	times[60] = 14402;  vals[60] = 86200;  /* 6/7/1939 June 7, 1939 */
	times[61] = 14772;  vals[61] = 85900;  /* 6/11/1940 June 11, 1940 */
	times[62] = 15142;  vals[62] = 86400;  /* 6/16/1941 June 16, 1941 */
	times[63] = 15507;  vals[63] = 143400;  /* 6/16/1942 June 16, 1942 */
	times[64] = 15884;  vals[64] = 174800;  /* 6/28/1943 June 28, 1943 */
	times[65] = 16251;  vals[65] = 155100;  /* 6/29/1944 June 29, 1944 */
	times[66] = 16617;  vals[66] = 108300;  /* 6/30/1945 June 30, 1945 */
	times[67] = 16969;  vals[67] = 92100;  /* 6/17/1946 June 17, 1946 */
	times[68] = 17341;  vals[68] = 134100;  /* 6/24/1947 June 24, 1947 */
	times[69] = 17705;  vals[69] = 144300;  /* 6/22/1948 June 22, 1948 */
	times[70] = 18066;  vals[70] = 103200;  /* 6/18/1949 June 18, 1949 */
	times[71] = 18441;  vals[71] = 122300;  /* 6/28/1950 June 28, 1950 */
	times[72] = 18800;  vals[72] = 97400;  /* 6/22/1951 June 22, 1951 */
	times[73] = 19157;  vals[73] = 122600;  /* 6/13/1952 June 13, 1952 */
	times[74] = 19529;  vals[74] = 223700;  /* 6/20/1953 June 20, 1953 */
	times[75] = 19910;  vals[75] = 91200;  /* 7/6/1954 July 6, 1954 */
	times[76] = 20273;  vals[76] = 108000;  /* 7/4/1955 July 4, 1955 */
	times[77] = 20619;  vals[77] = 161000;  /* 6/14/1956 June 14, 1956 */
	times[78] = 20988;  vals[78] = 138400;  /* 6/18/1957 June 18, 1957 */
	times[79] = 21340;  vals[79] = 121800;  /* 6/5/1958 June 5, 1958 */
	times[80] = 21727;  vals[80] = 137200;  /* 6/27/1959 June 27, 1959 */
	times[81] = 22094;  vals[81] = 87300;  /* 6/28/1960 June 28, 1960 */
	times[82] = 22447;  vals[82] = 108300;  /* 6/16/1961 June 16, 1961 */
	times[83] = 22825;  vals[83] = 145500;  /* 6/29/1962 June 29, 1962 */
	times[84] = 23175;  vals[84] = 138600;  /* 6/14/1963 June 14, 1963 */
	times[85] = 23553;  vals[85] = 228400;  /* 6/26/1964 June 26, 1964 */
	times[86] = 23930;  vals[86] = 168200;  /* 7/8/1965 July 8, 1965 */
	times[87] = 24269;  vals[87] = 74400;  /* 6/12/1966 June 12, 1966 */
	times[88] = 24650;  vals[88] = 221100;  /* 6/28/1967 June 28, 1967 */
	times[89] = 25020;  vals[89] = 157700;  /* 7/2/1968 July 2, 1968 */
	times[90] = 25397;  vals[90] = 134200;  /* 7/14/1969 July 14, 1969 */
	times[91] = 25735;  vals[91] = 169300;  /* 6/17/1970 June 17, 1970 */
	times[92] = 26116;  vals[92] = 170100;  /* 7/3/1971 July 3, 1971 */
	times[93] = 26472;  vals[93] = 187200;  /* 6/23/1972 June 23, 1972 */
	times[94] = 26835;  vals[94] = 103700;  /* 6/21/1973 June 21, 1973 */
	times[95] = 27211;  vals[95] = 192200;  /* 7/2/1974 July 2, 1974 */
	times[96] = 27580;  vals[96] = 217500;  /* 7/6/1975 July 6, 1975 */
	times[97] = 27924;  vals[97] = 126700;  /* 6/14/1976 June 14, 1976 */
	times[98] = 28292;  vals[98] = 84700;  /* 6/17/1977 June 17, 1977 */
	times[99] = 28639;  vals[99] = 163400;  /* 5/30/1978 May 30, 1978 */
	times[100] = 29017;  vals[100] = 113400;  /* 6/12/1979 June 12, 1979 */
	times[101] = 29404;  vals[101] = 112200;  /* 7/3/1980 July 3, 1980 */
	times[102] = 29745;  vals[102] = 162700;  /* 6/9/1981 June 9, 1981 */
	times[103] = 30136;  vals[103] = 166100;  /* 7/5/1982 July 5, 1982 */
	times[104] = 30488;  vals[104] = 117900;  /* 6/22/1983 June 22, 1983 */
	times[105] = 30860;  vals[105] = 124400;  /* 6/28/1984 June 28, 1984 */
	times[106] = 31216;  vals[106] = 86000;  /* 6/19/1985 June 19, 1985 */
	times[107] = 31579;  vals[107] = 162400;  /* 6/17/1986 June 17, 1986 */
	times[108] = 31946;  vals[108] = 74400;  /* 6/19/1987 June 19, 1987 */
	times[109] = 32311;  vals[109] = 84300;  /* 6/18/1988 June 18, 1988 */
	times[110] = 32686;  vals[110] = 101800;  /* 6/28/1989 June 28, 1989 */
	times[111] = 33045;  vals[111] = 97800;  /* 6/22/1990 June 22, 1990 */
	times[112] = 33406;  vals[112] = 153700;  /* 6/18/1991 June 18, 1991 */
	times[113] = 33791;  vals[113] = 88100;  /* 7/7/1992 July 7, 1992 */
	times[114] = 34127;  vals[114] = 102300;  /* 6/8/1993 June 8, 1993 */
	times[115] = 34480;  vals[115] = 92500;  /* 5/27/1994 May 27, 1994 */
	times[116] = 34877;  vals[116] = 174100;  /* 6/28/1995 June 28, 1995 */
	times[117] = 35239;  vals[117] = 181300;  /* 6/24/1996 June 24, 1996 */
	times[118] = 35602;  vals[118] = 223100;  /* 6/22/1997 June 22, 1997 */
	times[119] = 35988;  vals[119] = 130700;  /* 7/13/1998 July 13, 1998 */
	times[120] = 36339;  vals[120] = 135600;  /* 6/29/1999 June 29, 1999 */
	times[121] = 36692;  vals[121] = 90900;  /* 6/16/2000 June 16, 2000 */
	times[122] = 37063;  vals[122] = 69900;  /* 6/22/2001 June 22, 2001 */
	times[123] = 37433;  vals[123] = 104300;  /* 6/27/2002 June 27, 2002 */
	times[124] = 37779;  vals[124] = 120400;  /* 6/8/2003 June 8, 2003 */
	times[125] = 38153;  vals[125] = 72900;  /* 6/16/2004 June 16, 2004 */
	times[126] = 38534;  vals[126] = 147000;  /* 7/2/2005 July 2, 2005 */
	times[127] = 38881;  vals[127] = 103800;  /* 6/14/2006 June 14, 2006 */
	times[128] = 39248;  vals[128] = 117900;  /* 6/16/2007 June 16, 2007 */
	times[129] = 39612;  vals[129] = 155400;  /* 6/14/2008 June 14, 2008 */
	times[130] = 39973;  vals[130] = 130900;  /* 6/10/2009 June 10, 2009 */
	times[131] = 40342;  vals[131] = 156200;  /* 6/14/2010 June 14, 2010 */
	times[132] = 40694;  vals[132] = 261900;  /* 6/1/2011 June 1, 2011 */
	times[133] = 41072;  vals[133] = 109900;  /* 6/13/2012 June 13, 2012 */
	times[134] = 41438;  vals[134] = 139200;  /* 6/14/2013 June 14, 2013 */
	times[135] = 41796;  vals[135] = 154500;  /* 6/7/2014 June 7, 2014 */
	times[136] = 42166;  vals[136] = 140600;  /* 6/12/2015 June 12, 2015 */
	times[137] = 42510;  vals[137] = 103600;  /* 5/21/2016 May 21, 2016 */
	times[138] = 42902;  vals[138] = 142200;  /* 6/17/2017 June 17, 2017 */
	times[139] = 777180;  vals[139] = 1234;  /* 11/05/4027 November 5, 4027 */
	times[140] = 2959140;  vals[140] = 12345;  /* 11/06/10001 November 6, 10001 */
	times[141] = 2959506;  vals[141] = 123456;  /* 11/07/10002 November 7, 10002 */




	
	long long ifltab[250];
	zStructTimeSeries *tss, *tssOut;
	
	deleteFile("extended_139.dss");
	int status = zopen(ifltab, "extended_139.dss");
	if (status != STATUS_OKAY)
	{
		printf("\nError:  Yikes.. bad news with zopen(ts_write_irregular.dss)");
		return status;
	}
	
	tss = zstructTsNewIrregDoubles("//Garrison/FLOW-IN//IR-Century/Extended Dates/",
		vals, count, times, DAY_GRANULARITY, "01Jan1900", "cfs", "Inst-Val");
	status = ztsStore(ifltab, tss, 0);
	zstructFree(tss);
	if (status != STATUS_OKAY)
		return status;

	/*
	 READ DATA BACK IN
	*/
	int returnDoubles = 2;
	int dontReadQuality = 0;
	tssOut = zstructTsNew("//Garrison/FLOW-IN//IR-Century/Extended Dates/");

	status = ztsRetrieve(ifltab, tssOut, 0, returnDoubles, dontReadQuality);
	if (status != STATUS_OKAY) return status;
	//  Print out (values returned as doubles)
	if (tssOut->numberValues != count)
	{
		printf("\nError expected %d values, found %d values.", count, tssOut->numberValues);
		return -1;
	}

	char cdate[13], ctime[10];
	for (int i = 0; i < tssOut->numberValues; i++) {
		getDateAndTime(tssOut->times[i], tssOut->timeGranularitySeconds, tssOut->julianBaseDate,
			cdate, sizeof(cdate), ctime, sizeof(ctime));
		printf("%s, %s, value is %f\n", cdate, ctime, tssOut->doubleValues[i]);
	}


	return status;

}

int workbench()
{
	return RequestTimeArray();
	//return extendedDates();
}


int NativeSubMinute()
{
	// sub-minute native test.

	long long ifltab[250];
	zStructTimeSeries *tss1;

	float fvalues[__size];
	int status, i;

	memset(ifltab, 0, sizeof(ifltab));
	//  Open the DSS file; Create if it doesn't exist
	status = zopen(ifltab, "NativeSubMinute.dss");
	if (status != STATUS_OKAY) return status;

	//  Write a regular interval data set.  Gen up the data
	for (i = 0; i < __size; i++) {
		fvalues[i] = (float)i;
	}
	tss1 = zstructTsNewRegFloats("/Basin/Location/Flow//5Seconds/C/", fvalues, __size, "21Jan2001", "1200", "cfs", "Inst-Val");
	status = ztsStore(ifltab, tss1, 0);
	zstructFree(tss1);
	 return status;


}


int debugPairedDataLabels()
{
	long long ifltab[250];

	int _size = 22;
	int _curves = 12;

	float fordinates[22], fvalues[12][22];
	int status;
	char *fn = "PairedDataTesting-C.dss";
	deleteFile(fn);
	status = zopen(ifltab, fn);

	for (int i = 0; i < _size; i++) {
		fordinates[i] = (float)(i + 1) * 2;
		for (int j = 0; j < _curves; j++) {
			fvalues[j][i] = (float)(i + 1 + (j + 1) * 100000);
		}
	}



	zStructPairedData *pd = zstructPdNewFloats("/Basin/Location/Stage-Flow/Rating Table/C Sample//",
		fordinates, (float *)fvalues,
		_size, _curves, "Feet", "Linear", "Dollars", "Linear");

	char* labels = "curve1\0curve2\0curve3\0curve4\0curve5\0curve6\0curve7\0curve8\0curve9\0curve10\0curve11\0curve12\0";
	pd->labels = labels;
	pd->labelsLength = (12 * 7) + 3; // 12 curves * 7 char each, except 10-12 which are 8 characters (+3)


	status = zpdStore(ifltab, pd, 0);
	zstructFree(pd);

	zStructPairedData *pd3, *pd4;
	pd3 = zstructPdNew("/Basin/Location/Stage-Flow/Rating Table/C Sample//");
	pd3->startingCurve = 4;
	pd3->endingCurve = 8;
	pd3->startingOrdinate = 2;
	pd3->endingOrdinate = 5;

	pd4 = zstructPdNew("/Basin/Location/Stage-Flow/Rating Table/C Sample//");
	pd4->startingCurve = 4;
	pd4->endingCurve = 8;
	pd4->startingOrdinate = 2;
	pd4->endingOrdinate = 5;

	status = zpdRetrieve(ifltab, pd3, 1);
	float fordinates4[4], fvalues4[5][4];
	pd4->floatOrdinates = fordinates4;
	pd4->floatValues =(float*) fvalues4;
	int rowCount = pd4->endingOrdinate - pd4->startingOrdinate + 1;
	int colCount = pd4->endingCurve - pd4->startingCurve + 1;

	for (size_t i = 0; i < rowCount; i++)
	{
		fordinates4[i] = pd3->floatValues[i];
		for (size_t j = 0; j < colCount; j++)
		{
			size_t pos = i + j * rowCount;
			float f = -pd3->floatValues[pos];
			pd4->floatValues[pos] = f;

		}
	}

	char* labels2 = "CURVE4a\0CURVE5\0CURVE6\0CURVE7\0CURVE8\0";
	pd4->labels = labels2;
	pd4->labelsLength = 5 * 7 + 1; // 5 curves * 7 characters each  + 1 ( for extra 'a' in curve4a) 

	status = zpdStore(ifltab, pd4, 0);


	if (status != STATUS_OKAY) return status;

	return 0;
}

