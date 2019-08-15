#include "pch.h"
#include <stdio.h>
#include <string.h>
#include "heclib.h"

//  An example of storing and retrieving a single text string

int SampleText1(const char *filename, const char* path, bool read, bool write)
{
	long long ifltab[250];
	char textStuff[] = "This is a text message that is being written to HEC-DSS";
	zStructText *textStruct;
	int status;

	//  Open the DSS file.  
	status = zopen(ifltab, filename);
	if (status != STATUS_OKAY) return status;

	if (write)
	{//  Store the text string
		textStruct = zstructTextStringNew(path, textStuff);
		status = ztextStore(ifltab, textStruct);
		zstructFree(textStruct);
		if (status != STATUS_OKAY) return status;
	}
	if (read)
	{
		//  Retrieve
		textStruct = zstructTextNew(path);
		status = ztextRetrieve(ifltab, textStruct);

		printf("text ==>%s<==\n", textStruct->textString);
		if (strcmp(textStuff, textStruct->textString) != 0)
		{
			printf("\nstrings are different...");
			return -1;
		}
		zstructFree(textStruct);
		if (status != STATUS_OKAY) return status;
	}
	

	//  When all done (near end of program), close the file
	zclose(ifltab);

	return 0;
}

 