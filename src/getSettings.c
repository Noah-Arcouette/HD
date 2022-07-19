#include "structures.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
--config, -c  : set config file

--inc, -i     : add include dir
--src, -s     : add source dir
--lib
--path
--flag

--bin
--obj
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
				case 'l':
					#include "movef.c"

					saPush(&settings->libs, argv[i]);

					printf("\x1b[32mLibrary\x1b[39m      : %s\n", settings->libs.items[settings->libs.size-1]);

					break;
				case 'v':
					#include "movef.c"
					
					settings->version = (char*)realloc(settings->version, (strlen(argv[i])+1)*sizeof(char));
					strcpy(settings->version, argv[i]);
					
					printf("\x1b[32mVersion\x1b[39m      : %s\n", settings->version);

					break;
				case 'n':
					#include "movef.c"

					settings->name = (char*)realloc(settings->name, (strlen(argv[i])+1)*sizeof(char));
					strcpy(settings->name, argv[i]);
					
					printf("\x1b[32mName\x1b[39m         : %s\n", settings->name);

					break;
				case 'o':
					#include "movef.c"

					settings->objDir = (char*)realloc(settings->objDir, (strlen(argv[i])+1)*sizeof(char));
					strcpy(settings->objDir, argv[i]);
					
					printf("\x1b[32mObject Path\x1b[39m  : %s\n", settings->objDir);

					break;
				case 'b':
					#include "movef.c"

					settings->binDir = (char*)realloc(settings->binDir, (strlen(argv[i])+1)*sizeof(char));
					strcpy(settings->binDir, argv[i]);
					
					printf("\x1b[32mBinary Path\x1b[39m  : %s\n", settings->binDir);

					break;
				case 'f':
					#include "movef.c"

					saPush(&settings->flags, argv[i]);

					printf("\x1b[32mFlags\x1b[39m        : %s\n", settings->flags.items[settings->flags.size-1]);

					break;
				case 'p':
					#include "movef.c"

					saPush(&settings->libDirs, argv[i]);

					printf("\x1b[32mLibrary Path\x1b[39m : %s\n", settings->libDirs.items[settings->libDirs.size-1]);

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
