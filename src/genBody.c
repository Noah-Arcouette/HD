#include "structures.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int genBody (char **makefile, struct hd_settings s, struct hd_file *files)
{
	char *include;

	// loop through files
	for (register size_t i = 0; !files[i].term; i++)
	{
		printf("\x1b[1;39mFile         ┃ %s\n", files[i].path);
		// loop through include files
		for (register size_t j = 0; j<files[i].files.size; j++)
		{
			// find include file
			include = includeSearch(files[i].files.items[j], s);
			if (include)
			{
				// build makefile section
				printf("\x1b[1;32mFound        \x1b[39m┃ \x1b[35m%s \x1b[39mat \x1b[35m%s\n", 
					files[i].files.items[j],
					include
				);

				free(include);
			}
			else
			{
				return 1;
			}
		}

		puts("\x1b[39m             ┃");
	}

	return 0;
}
