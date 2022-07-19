#include <stdio.h>
#include "info.h"
#include <macsv.h>
#include <stdlib.h>
#include <msap.h>
#include <string.h>
#include "getFiles.h"

int main ()
{
	sa files = { NULL, 0 };

	getFiles("./test.c", &files);

	for (register size_t i = 0; i<files.size; i++)
	{
		puts(files.items[i]);
	}

	saFree(files);

	return 0;
}
