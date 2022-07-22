#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "functions.h"
#include <msap.h>
#include <macsv.h>

int useConfig (char *file, struct hd_settings *s)
{
	FILE *fp = fopen(file, "r");

	if (fp == NULL)
	{
		printf("\x1b[1;31mCan not open \x1b[39m┃ \x1b[35m%s\n",
			file
		);

		return 1;
	}

	// read file
	fseek(fp, 0, SEEK_END);
	const size_t size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char *raw = (char*)malloc(sizeof(char) * size);
	fread(raw, size, 1, fp);

	// close file
	fclose(fp);

	acsv config = acsvParse(raw);
	free(raw);

	register ssize_t hold;
	register sa saHold;
	register size_t i;

	if ((hold = acsvSearch(config, "include")) >= 0)
	{
		saHold = saSplit(config.vals[hold], ' ');

		for (i = 0; i<saHold.size; i++)
		{
			saPush(&s->incDirs, saHold.items[i]);
		}

		saFree(saHold);

		printf("\x1b[1;32mInclude Path \x1b[39m┃ %s\n", 
			config.vals[hold]);
	}

	if ((hold = acsvSearch(config, "source")) >= 0)
	{
		saHold = saSplit(config.vals[hold], ' ');

		for (i = 0; i<saHold.size; i++)
		{
			saPush(&s->srcDirs, saHold.items[i]);
		}

		saFree(saHold);

		printf("\x1b[1;32mSource Path  \x1b[39m┃ %s\n", 
			config.vals[hold]);
	}

	if ((hold = acsvSearch(config, "library")) >= 0)
	{
		saHold = saSplit(config.vals[hold], ' ');

		for (i = 0; i<saHold.size; i++)
		{
			saPush(&s->libs, saHold.items[i]);
		}

		saFree(saHold);

		printf("\x1b[1;32mLibrary      \x1b[39m┃ %s\n", 
			config.vals[hold]);
	}

	if ((hold = acsvSearch(config, "path")) >= 0)
	{
		saHold = saSplit(config.vals[hold], ' ');

		for (i = 0; i<saHold.size; i++)
		{
			saPush(&s->libDirs, saHold.items[i]);
		}

		saFree(saHold);

		printf("\x1b[1;32mLibrary Path \x1b[39m┃ %s\n", 
			config.vals[hold]);
	}

/*
	flag: -g -Wall -Wextra -O2 -std=gnu18 -D_GNU_SOURCE;
	name: hd;
	version: 1.3;
	makefile: makefile.test;
*/

	acsvFree(config);

	return 0;
}
