#include <stdio.h>
#include <string.h>
#include <math.h>// for fabs()
#include "heclib.h"
#include "utility.h"


#define ROWS_  9 // number of rows

int SamplePairedData(const char *filename, const char* path, int read, int write)
{
	long long ifltab[250];
	zStructPairedData *pd_in, *pd_out;
	float fordinates[ROWS_], fvalues[2][ROWS_];
	int status, i, row; 


	//  Open the DSS file; Create if it doesn't exist
	status = zopen(ifltab, filename);
	if (status != STATUS_OKAY) return status;

	//  Write a rating table data set.  Gen up the data
	for (i = 0; i < ROWS_; i++) {
		fordinates[i] = (float)i;
		fvalues[0][i] = (float)(10 * i);
		fvalues[1][i] = (float)(100 * i);
	}
	pd_in = zstructPdNewFloats(path, fordinates, (float *)fvalues,
		ROWS_, 2, "Feet", "Unt", "cfs", "Unt");
	status = zpdStore(ifltab, pd_in, 0);
	zstructFree(pd_in);
	if (status != STATUS_OKAY) return status;

	//  Now retrieve the data
	pd_out = zstructPdNew(path);
	status = zpdRetrieve(ifltab, pd_out, 1);
	if (status != STATUS_OKAY) return status;

	printPdStruct(pd_out);
	// verify values 

	for (row = 0; row < pd_out->numberOrdinates; row++) {
		 if( fabs( pd_out->floatOrdinates[row] - (float) row) > 0.00001)
			 return -1;

	}
	for (row = 0; row < pd_out->numberOrdinates; row++) {
		//for (column = 0; column < pd_out->numberCurves; column++) {
			//pos = row + column * pds->numberOrdinates;
		if(    fabs(pd_out->floatValues[row ] - (float)(10 * row) ) > 0.000001
			|| fabs(pd_out->floatValues[row +  pd_out->numberOrdinates] - (float)(100 * row)) > 0.000001
				)
					return -1;
	//}
   }

	
	zstructFree(pd_out);
	if (status != STATUS_OKAY) return status;

	zclose(ifltab);
	return 0;
}


