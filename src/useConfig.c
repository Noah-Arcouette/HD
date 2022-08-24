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

	if ((hold = acsvSearch(config, "flag")) >= 0)
	{
		saHold = saSplit(config.vals[hold], ' ');

		for (i = 0; i<saHold.size; i++)
		{
			saPush(&s->flags, saHold.items[i]);
		}

		saFree(saHold);

		printf("\x1b[1;32mFlag         \x1b[39m┃ %s\n", 
			config.vals[hold]);
	}

	if ((hold = acsvSearch(config, "testing")) >= 0)
	{
		saHold = saSplit(config.vals[hold], ' ');

		for (i = 0; i<saHold.size; i++)
		{
			saPush(&s->testing, saHold.items[i]);
		}

		saFree(saHold);

		printf("\x1b[1;32mTest File    \x1b[39m┃ %s\n", 
			config.vals[hold]);
	}

	if ((hold = acsvSearch(config, "name")) >= 0)
	{
		s->name = (char*)realloc(s->name, sizeof(char) * (strlen(config.vals[hold])+1));
		strcpy(s->name, config.vals[hold]);

		printf("\x1b[1;32mName         \x1b[39m┃ %s\n", 
			config.vals[hold]);
	}

	if ((hold = acsvSearch(config, "version")) >= 0)
	{
		s->version = (char*)realloc(s->version, sizeof(char) * (strlen(config.vals[hold])+1));
		strcpy(s->version, config.vals[hold]);

		printf("\x1b[1;32mVersion      \x1b[39m┃ %s\n", 
			config.vals[hold]);
	}

	if ((hold = acsvSearch(config, "binary")) >= 0)
	{
		s->binDir = (char*)realloc(s->binDir, sizeof(char) * (strlen(config.vals[hold])+1));
		strcpy(s->binDir, config.vals[hold]);

		printf("\x1b[1;32mBinary Path  \x1b[39m┃ %s\n", 
			config.vals[hold]);
	}

	if ((hold = acsvSearch(config, "object")) >= 0)
	{
		s->objDir = (char*)realloc(s->objDir, sizeof(char) * (strlen(config.vals[hold])+1));
		strcpy(s->objDir, config.vals[hold]);

		printf("\x1b[1;32mObject Path  \x1b[39m┃ %s\n", 
			config.vals[hold]);
	}

	if ((hold = acsvSearch(config, "makefile")) >= 0)
	{
		s->makefile = (char*)realloc(s->makefile, sizeof(char) * (strlen(config.vals[hold])+1));
		strcpy(s->makefile, config.vals[hold]);

		printf("\x1b[1;32mMakeFile     \x1b[39m┃ %s\n", 
			config.vals[hold]);
	}

	if ((hold = acsvSearch(config, "mode")) >= 0)
	{
		if (!strcmp(config.vals[hold], "app") || !strcmp(config.vals[hold], "application"))
		{
			s->mode = HD_MODE_APP;

			printf("\x1b[1;32mMode         \x1b[39m┃ Application\n");
		}
		else if (!strcmp(config.vals[hold], "dynamic"))
		{
			s->mode = HD_MODE_DYNAMIC;

			printf("\x1b[1;32mMode         \x1b[39m┃ Dynamic Library\n");
		}
		else if (!strcmp(config.vals[hold], "static"))
		{
			s->mode = HD_MODE_STATIC;

			printf("\x1b[1;32mMode         \x1b[39m┃ Static Library\n");
		}
		else
		{
			printf("\x1b[1;31mERROR        \x1b[39m┃ Unknown mode \x1b[35m%s\n", config.vals[hold]);

			return 1;
		}
	}

	acsvFree(config);

	return 0;
}
