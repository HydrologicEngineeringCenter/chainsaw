#include <stdio.h>
#include <string.h>
#include <math.h>// for fabs()
#include "heclib.h"
#include "utility.h"
#define ROWS_  7 // number of rows
#define CURVES_ 3
int SamplePairedDataDoubles(const char *filename, const char* path, int read, int write)
{
	long long ifltab[250];
	zStructPairedData *pds1, *pds2, *pds3;
	double dordinates[ROWS_], dvalues[ROWS_];
	double d;

	int status, i, j, error, version;

	//  Open the DSS file; Create if it doesn't exist
	status = zopen(ifltab, filename);
	if (status != STATUS_OKAY) return status;

	version = zgetVersion(ifltab);

	if (version == 6) // version 6 does not support piecewise saving of paried data.
	{
		zclose(ifltab);
		return 0;
	}


	if (write)
	{
		//  Pre-allocate space for ROWS_ rows for a family of 10 curves
		//  Gen up the oridnates
		for (i = 0; i < ROWS_; i++) {
			dordinates[i] = (double)(i + 1);
		}
		pds1 = zstructPdNew(path);
		pds1->numberCurves = CURVES_;
		pds1->numberOrdinates = ROWS_;
		pds1->doubleOrdinates = dordinates;
		pds1->unitsIndependent = "feet";
		pds1->typeIndependent = "linear";
		pds1->unitsDependent = "dollars";
		pds1->typeDependent = "linear";
		//pds1->labels = 1;  //  b
		status = zpdStore(ifltab, pds1, 10);	// Flag 10 allocates space
		zstructFree(pds1);
		if (status != STATUS_OKAY) return status;
		/*
	Row       Ordinate       Curve 0         Curve 1         Curve 2
	 0       1.000000        10.000000       20.000000       30.000000
	 1       2.000000        11.000000       22.000000       33.000000
	 2       3.000000        12.000000       24.000000       36.000000
	 3       4.000000        13.000000       26.000000       39.000000
	 4       5.000000        14.000000       28.000000       42.000000
	 5       6.000000        15.000000       30.000000       45.000000
	 6       7.000000        16.000000       32.000000       48.000000

		*/
		//  Now write each of the curves separately 
		for (j = 0; j < CURVES_; j++) {
			for (i = 0; i < ROWS_; i++) {
				//d = ((double)j * 100.0) + ((double)i * 10.0);
				d = (i + 10)*(j + 1);
				printf("\n [%d][%d] = %f", j, i, d);
				dvalues[i] = d;
			}
			pds2 = zstructPdNew(path);
			//  First curve is #1, not #0 (by convention)

			pds2->startingCurve = j + 1;
			pds2->endingCurve = pds2->startingCurve;
			pds2->doubleValues = dvalues;
			status = zpdStore(ifltab, pds2, 0);
			zstructFree(pds2);
			if (status != STATUS_OKAY)
			{
				printf("\nERORR... SamplePairedDataDoubles.zpdStore()");
				return status;
			}
		}

		if (printPairedDataRecordSize(ifltab, path) != 0)
		{
			return -1;
		}
	}

	if (read)
	{
		//  Now retrieve the data
		pds3 = zstructPdNew(path);
		status = zpdRetrieve(ifltab, pds3, 2);
		//  print a part of the struct
		printPdStruct(pds3);
		error = 0;

		// Verifty values and text is read back out the same as entered. 
		if (strcmp("feet", pds3->unitsIndependent) != 0)
		{
			printf("\nError: expected \"feet\" result = %s", pds3->unitsIndependent);
			error = -1;
		}
		if (strcmp("linear", pds3->typeIndependent) != 0)
		{
			printf("\nError: expected \"linear\" result = %s", pds3->typeIndependent);
			error = -1;
		}

		if (strcmp("linear", pds3->typeIndependent) != 0)
		{
			printf("\nError: expected \"linear\" result = %s", pds3->typeIndependent);
			error = -1;
		}

		if (strcmp("dollars", pds3->unitsDependent) != 0)
		{
			printf("\nError: expected \"dollars\" result = %s", pds3->unitsDependent);
			error = -1;
		}


		if (pds3->numberCurves != 3)
		{
			printf("\nError: expected 3 actual = %d", pds3->numberCurves);
			error = -1;
		}

		if (fabs(pds3->doubleValues[7] - 20) > 0.1)  // position 7 is first point in curve 2
		{
			printf("\nError: expected 20  actual = %f", pds3->doubleValues[7]);
			error = -1;
		}

		zstructFree(pds3);
		if (status != STATUS_OKAY) return status;
		if (error != 0)
		{
			return -1;
		}
	}
	zclose(ifltab);
	return 0;
}

