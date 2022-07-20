#include "structures.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <msap.h>
#include <errno.h>
#include <sys/stat.h>

int checkDirs (sa s)
{
	DIR* dir;
	for (register size_t i = 0; i<s.size; i++)
	{
		dir = opendir(s.items[i]);

		if (dir)
		{
			printf("\x1b[32mExists \x1b[39m      ┃ Directory \x1b[32m%s\n", s.items[i]);

			closedir(dir);
		}
		else if (ENOENT == errno)
		{
			mkdir(s.items[i], S_IRWXU);

			printf("\x1b[33mCreated \x1b[39m     ┃ Directory \x1b[32m%s\n", s.items[i]);
		}
		else
		{
			printf("\x1b[31mError \x1b[39m       ┃ Directory \x1b[32m%s\n", s.items[i]);

			return 1;
		}
	}

	return 0;
}

int runChecks (struct hd_settings *s)
{
	printf("\x1b[1m");

	// Source path
	printf("\x1b[35mSource Path \x1b[39m ┃\n");

	if (s->srcDirs.size < 1)
	{
		saPush(&s->srcDirs, "./src/");
		printf("\x1b[33mWARNING      \x1b[39m┃ Setting default I.E \x1b[32m./src/\n");
	}

	if (checkDirs(s->srcDirs))
	{
		return 1;
	}

	// Include path
	printf("\x1b[39m             ┃\n\x1b[35mInclude Path\x1b[39m ┃\n");

	if (s->incDirs.size < 1)
	{
		saPush(&s->incDirs, "./inc/");
		printf("\x1b[33mWARNING      \x1b[39m┃ Setting default I.E \x1b[32m./inc/\n");
	}

	if (checkDirs(s->incDirs))
	{
		return 1;
	}

	// Library Path
	printf("\x1b[39m             ┃\n\x1b[35mLibrary Path\x1b[39m ┃\n");

	if (s->libDirs.size < 1)
	{
		printf("\x1b[32mDISCLUDED    \x1b[39m┃ No library path\n");
	}
	else if (checkDirs(s->libDirs))
	{
		return 1;
	}

	// Binary Path
	printf("\x1b[39m             ┃\n\x1b[35mBinary Path \x1b[39m ┃\n");

	if (!s->binDir)
	{
		s->binDir = malloc(sizeof("./bin/"));
		strcpy(s->binDir, "./bin/");

		printf("\x1b[33mWARNING      \x1b[39m┃ Setting default I.E \x1b[32m./bin/\n");
	}

	DIR* dir = opendir(s->binDir);

	if (dir)
	{
		printf("\x1b[32mExists \x1b[39m      ┃ Directory \x1b[32m%s\n", s->binDir);

		closedir(dir);
	}
	else if (ENOENT == errno)
	{
		mkdir(s->binDir, S_IRWXU);

		printf("\x1b[33mCreated \x1b[39m     ┃ Directory \x1b[32m%s\n", s->binDir);
	}
	else
	{
		printf("\x1b[31mError \x1b[39m       ┃ Directory \x1b[32m%s\n", s->binDir);

		return 1;
	}

	// Object Path
	printf("\x1b[39m             ┃\n\x1b[35mObject Path \x1b[39m ┃\n");

	if (!s->objDir)
	{
		s->objDir = malloc(sizeof("./obj/"));
		strcpy(s->objDir, "./obj/");

		printf("\x1b[33mWARNING      \x1b[39m┃ Setting default I.E \x1b[32m%s\n", s->objDir);
	}

	dir = opendir(s->objDir);

	if (dir)
	{
		printf("\x1b[32mExists \x1b[39m      ┃ Directory \x1b[32m%s\n", s->objDir);

		closedir(dir);
	}
	else if (ENOENT == errno)
	{
		mkdir(s->objDir, S_IRWXU);

		printf("\x1b[33mCreated \x1b[39m     ┃ Directory \x1b[32m%s\n", s->objDir);
	}
	else
	{
		printf("\x1b[31mError \x1b[39m       ┃ Directory \x1b[32m%s\n", s->objDir);

		return 1;
	}

	// name
	printf("\x1b[39m             ┃\n\x1b[35mName        \x1b[39m ┃\n");

	if (!s->name)
	{
		s->name = malloc(sizeof("newProject"));
		strcpy(s->name, "newProject");

		printf("\x1b[33mWARNING      \x1b[39m┃ Setting default I.E \x1b[32m%s\n", s->name);
	}
	else
	{
		printf("\x1b[32mValue        \x1b[39m┃ \x1b[32m%s\n", s->name);
	}

	// version
	printf("\x1b[39m             ┃\n\x1b[35mVersion     \x1b[39m ┃\n");

	if (!s->version)
	{
		s->version = malloc(sizeof("0.0"));
		strcpy(s->version, "0.0");

		printf("\x1b[33mWARNING      \x1b[39m┃ Setting default I.E \x1b[32m%s\n", s->version);
	}
	else
	{
		printf("\x1b[32mValue        \x1b[39m┃ \x1b[32m%s\n", s->version);
	}
	return 0;
}
