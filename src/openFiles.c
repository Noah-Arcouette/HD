#include "structures.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int openFiles (struct hd_settings s, struct hd_file **files)
{
	// initialize files
	*files = (struct hd_file*)malloc(1 * sizeof(struct hd_file));
	(*files)[0].term        = 1;
	(*files)[0].path        = NULL;
	(*files)[0].files.size  = 0;
	(*files)[0].files.items = NULL;

	sa src = s.srcDirs;

	struct dirent *pDirent;
	DIR *pDir;

	printf("\x1b[1;35mSources      \x1b[39m┃\n");

	// open and parse all source files
	for (register size_t i = 0; i<src.size; i++)
	{		
		pDir = opendir(src.items[i]);

		while ((pDirent = readdir(pDir)) != NULL) 
		{
			if (strcasestr(pDirent->d_name, ".c"))
			{
				printf("             ┃ %s/%s\n", src.items[i], pDirent->d_name);
			}
		}

        closedir(pDir);
	}

	return 0;
}
