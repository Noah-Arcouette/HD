#include "structures.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char* getDir (char *dir, char *file)
{
	char *out = (char*)malloc((strlen(dir)+2+strlen(file)) * sizeof(char));
	// handle nested dirs
	strcpy(out, dir);
	strcat(out, "/");
	strcat(out, file);

	if (!access(out, F_OK)) 
	{
	    return out;
	}

	return NULL;
}

char* includeSearch (char *file, struct hd_settings s)
{
	char *fileout;

	for (register size_t i = 0; i<s.incDirs.size; i++)
	{
		fileout = getDir(s.incDirs.items[i], file);

		if (fileout == NULL)
		{
			continue;
		}

		return fileout;
	}

	printf("\x1b[1;31mERROR\x1b[39m        ┃ Can not find file \x1b[32m%s\n", file);

	return NULL;
}
