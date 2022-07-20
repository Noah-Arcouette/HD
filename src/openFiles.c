#include "structures.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int openFiles (struct hd_settings s, struct hd_file **files)
{
	// initialize files
	size_t size = 1;
	*files = (struct hd_file*)malloc(1 * sizeof(struct hd_file));
	(*files)[0].term        = 1;
	(*files)[0].path        = NULL;
	(*files)[0].files.size  = 0;
	(*files)[0].files.items = NULL;

	sa src = s.srcDirs;

	struct dirent *pDirent;
	DIR *pDir;

	printf("\x1b[1m");

	// open and parse all source files
	for (register size_t i = 0; i<src.size; i++)
	{		
		pDir = opendir(src.items[i]);

		while ((pDirent = readdir(pDir)) != NULL) 
		{
			if (pDirent->d_type == DT_REG && strcasestr(pDirent->d_name, ".c"))
			{
				// resize array
				*files = (struct hd_file*)realloc(*files, ++size * sizeof(struct hd_file));
				(*files)[size-2].term = 0;

				// add path
				(*files)[size-2].path        = 
				(char*)malloc((
					strlen(src.items[i]) +
					strlen(pDirent->d_name) +
					2
				) * sizeof(char));
				strcpy((*files)[size-2].path, src.items[i]);
				strcat((*files)[size-2].path, "/");
				strcat((*files)[size-2].path, pDirent->d_name);

				// set up string array
				(*files)[size-2].files.size  = 0;
				(*files)[size-2].files.items = NULL;

				// print data
				printf("File         ┃ %s/%s\n", src.items[i], pDirent->d_name);
			
				// get includes
				if (getFiles(
					(*files)[size-2].path,
					&((*files)[size-2].files)
				))
				{
					// error
					puts("\x1b[31mFatal        \x1b[39m┃");
					(*files)[size-1].term = 1;
					closedir(pDir);

					return 1;
					break;
				}
				else
				{
					puts("\x1b[32mIncludes     \x1b[39m┃");

					for (register size_t j = 0; j<(*files)[size-2].files.size; j++)
					{
						printf("             ┃ \x1b[35m %s\x1b[39m\n", 
							(*files)[size-2].files.items[j]
						);
					}

					puts("             ┃");
				}
			}
		}

        closedir(pDir);
	}

	(*files)[size-1].term = 1;

	return 0;
}
