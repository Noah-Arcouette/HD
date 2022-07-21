#include "structures.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getIso (char *file, char **out)
{
	const size_t size = strlen(file)+10;

	*out = (char*)realloc(*out, size * sizeof(char));
	strcpy(*out, "${OBJ}/");

	for (register size_t i = size-13; i>0 && file[i] != '/'; i--)
	{
		strncat(*out, &file[i], 1);
	}

	strcat(*out, ".o");
}

int genBody (char **makefile, struct hd_settings s, struct hd_file *files)
{
	char *include;
	char *iso = NULL;
	register size_t size = strlen(*makefile)+1;

	sa isos = { NULL, 0 };

	// loop through files
	for (register size_t i = 0; !files[i].term; i++)
	{
		// <objpath>/<isolet>.o: <path> ...
		getIso(files[i].path, &iso);

		size += strlen(files[i].path) + 3 + strlen(iso);
		*makefile = (char*)realloc(*makefile, size*sizeof(char));

		strcat(*makefile, iso);
		strcat(*makefile, ": ");
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
		// \t${CC} ${CFLAGS} -o <iso>.o <path>\n
		size += 24 + strlen(iso) + strlen(files[i].path);
		*makefile = (char*)realloc(*makefile, size * sizeof(char));
		strcat(*makefile, "\n\t${CC} ${CFLAGS} -o ");
		strcat(*makefile, iso);
		strcat(*makefile, " ");
		strcat(*makefile, files[i].path);
		strcat(*makefile, "\n\n");

		saPush(&isos, iso);

		puts("\x1b[39m             ┃");
	}
	free(iso);

	char *isosS = saJoin(isos, ' ');

	
	// ${OUT}: <isos>\n
	// \t${CC} ${CFLAGS} ${LIB} -o ${OUT} <isos> ${LIBS}
	size += 51 + (2*strlen(isosS));
	*makefile = (char*)realloc(*makefile, size * sizeof(char));

	strcat(*makefile, "${OUT}: ");
	strcat(*makefile, isosS);
	strcat(*makefile, "\n\t${CC} ${CFLAGS} ${LIB} -o ${OUT} ");
	strcat(*makefile, isosS);
	strcat(*makefile, " ${LIBS}\n");

	free(isosS);

	saFree(isos);

	return 0;
}