#include "structures.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getIso (char *file)
{
	const size_t size = strlen(file)-3;

	char *out = (char*)malloc(size * sizeof(char));
	strcpy(out, "");

	for (register size_t i = size; i>0 && file[i] != '/'; i--)
	{
		strncat(out, &file[i], 1);
	}

	return out;
}

int genBody (char **makefile, struct hd_settings s, struct hd_file *files)
{
	char *include;
	char *iso;
	register size_t size = strlen(*makefile)+1;

	// loop through files
	for (register size_t i = 0; !files[i].term; i++)
	{
		// <objpath>/<isolet>.o: <path> ...
		iso = getIso(files[i].path);

		size += strlen(files[i].path) + 6 + strlen(s.objDir) + strlen(iso);
		*makefile = (char*)realloc(*makefile, size*sizeof(char));

		strcat(*makefile, s.objDir);
		strcat(*makefile, "/");
		strcat(*makefile, iso);
		strcat(*makefile, ".o: ");
		strcat(*makefile, files[i].path);
		strcat(*makefile, " ");


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

				size += strlen(include)+1;
				*makefile = (char*)realloc(*makefile, size * sizeof(char));

				strcat(*makefile, include);
				strcat(*makefile, " ");

				free(include);
			}
			else
			{
				return 1;
			}
		}
		// \t${CC} ${CFLAGS} -o ${OBJ}/<iso>.o <path>\n
		size += 33 + strlen(iso) + strlen(files[i].path);
		*makefile = (char*)realloc(*makefile, size * sizeof(char));
		strcat(*makefile, "\n\t${CC} ${CFLAGS} -o ${OBJ}/");
		strcat(*makefile, iso);
		strcat(*makefile, ".o ");
		strcat(*makefile, files[i].path);
		strcat(*makefile, "\n\n");

		free(iso);

		puts("\x1b[39m             ┃");
	}

	return 0;
}
