#include "structures.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
--config, -c  : set config file

--inc, -i     : add include dir
--src, -s     : add source dir
--lib, -l     : add lib
--path, -p    : add to lib path
--flag, -f    : add flag

--bin, -b     : set output dir
--obj, -o     : set output for objects
--name
--version
*/

int getSettings (
	struct hd_settings *settings, 
	size_t argc, 
	char** argv
)
{	
	printf("\x1b[1m");

	for (register size_t i = 1; i<argc; i++)
	{
		// string parameter
		if (argv[i][0] == '-' && argv[i][1] == '-')
		{

		}
		// char parameter
		else if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
				case 'v':
					#include "movef.c"
					
					settings->version = (char*)realloc(settings->version, (strlen(argv[i])+1)*sizeof(char));
					strcpy(settings->version, argv[i]);
					
					printf("\x1b[32mVersion\x1b[39m: %s\n", settings->version);

					break;
				case 'n':
					#include "movef.c"

					settings->name = (char*)realloc(settings->name, (strlen(argv[i])+1)*sizeof(char));
					strcpy(settings->name, argv[i]);
					
					printf("\x1b[32mName\x1b[39m: %s\n", settings->name);

					break;
				default:
					printf("\x1b[31mERROR\x1b[39m: Unknow option \x1b[32m%s\n", argv[i]);
					return 1;

					break;
			}
		}
		// IDK
		else
		{

		}
	}

	return 0;
}
