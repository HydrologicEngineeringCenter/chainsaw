#include <stdio.h>
#include "heclib.h"

void printPdStruct(zStructPairedData *pds)
{

	int row;
	int column;
	int pos;

	printf("\nRow \t  Ordinate \t");
	for (column = 0; column < pds->numberCurves; column++) {
		printf(" Curve %d \t", column+1);
	}
	printf("\n");

	for (row = 0; row < pds->numberOrdinates; row++) {
		printf(" %d \t", row+1);
		if (pds->floatOrdinates) {
			printf(" %f \t", pds->floatOrdinates[row]);
		}
		else {
			printf(" %f \t", pds->doubleOrdinates[row]);
		}
		for (column = 0; column < pds->numberCurves; column++) {
			pos = row + column * pds->numberOrdinates;
			if (pds->floatValues) {
				printf(" %f \t", pds->floatValues[pos]);
			}
			else {
				printf(" %f \t", pds->doubleValues[pos]);
			}
		}
		printf("\n");
	}
}

int printPairedDataRecordSize(long long ifltab[250], const char* path)
{
	int status;
	zStructRecordSize *recordSize;
	//  Get the data type, number of ordinates and curves for this data set
	recordSize = zstructRecordSizeNew(path);
	status = zgetRecordSize(ifltab, recordSize);


	if (status != STATUS_OKAY) {
		zstructFree((void *)recordSize);
		return status;
	}
	if (recordSize->dataType == DATA_TYPE_PD) {
		printf("Paired Data floats, number curves: %d, number ordinates: %d\n",
			recordSize->pdNumberCurves, recordSize->pdNumberOrdinates);
	}
	else if (recordSize->dataType == DATA_TYPE_PDD) {
		printf("Paired Data doubles, number curves: %d, number ordinates: %d\n",
			recordSize->pdNumberCurves, recordSize->pdNumberOrdinates);
	}
	else {
		printf("Not paired data, data type: %d\n", recordSize->dataType);
	}

	if (recordSize->dataType != DATA_TYPE_PDD)
	{
		printf("\nError:  Expected data type of double paired data.");
		zstructFree((void *)recordSize);
		return -1;
	}
	zstructFree((void *)recordSize);
	return 0;
}


