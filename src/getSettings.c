#include "structures.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
--config, -c  : set config file
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
			if (!strcmp(argv[i], "--version"))
			{
				#include "movef.c"
					
				settings->version = (char*)realloc(settings->version, (strlen(argv[i])+1)*sizeof(char));
				strcpy(settings->version, argv[i]);
				
				printf("\x1b[32mVersion\x1b[39m      ┃ %s\n", settings->version);
			}
			else if (!strcmp(argv[i], "--include"))
			{
				#include "movef.c"

				saPush(&settings->incDirs, argv[i]);

				printf("\x1b[32mInclude Path\x1b[39m ┃ %s\n", settings->incDirs.items[settings->incDirs.size-1]);
			}
			else if (!strcmp(argv[i], "--source"))
			{
				#include "movef.c"

				saPush(&settings->srcDirs, argv[i]);

				printf("\x1b[32mSource Path\x1b[39m  ┃ %s\n", settings->srcDirs.items[settings->srcDirs.size-1]);
			}
			else if (!strcmp(argv[i], "--name"))
			{
				#include "movef.c"

				settings->name = (char*)realloc(settings->name, (strlen(argv[i])+1)*sizeof(char));
				strcpy(settings->name, argv[i]);
				
				printf("\x1b[32mName\x1b[39m         ┃ %s\n", settings->name);
			}
			else if (!strcmp(argv[i], "--flag"))
			{
				#include "movef.c"

				saPush(&settings->flags, argv[i]);

				printf("\x1b[32mFlags\x1b[39m        ┃ %s\n", settings->flags.items[settings->flags.size-1]);
			}
			else if (!strcmp(argv[i], "--path"))
			{
				#include "movef.c"

				saPush(&settings->libDirs, argv[i]);

				printf("\x1b[32mLibrary Path\x1b[39m ┃ %s\n", settings->libDirs.items[settings->libDirs.size-1]);
			}
			else if (!strcmp(argv[i], "--object"))
			{
				#include "movef.c"

				settings->objDir = (char*)realloc(settings->objDir, (strlen(argv[i])+1)*sizeof(char));
				strcpy(settings->objDir, argv[i]);
				
				printf("\x1b[32mObject Path\x1b[39m  ┃ %s\n", settings->objDir);
			}
			else if (!strcmp(argv[i], "--binary"))
			{
				#include "movef.c"

				settings->binDir = (char*)realloc(settings->binDir, (strlen(argv[i])+1)*sizeof(char));
				strcpy(settings->binDir, argv[i]);
				
				printf("\x1b[32mBinary Path\x1b[39m  ┃ %s\n", settings->binDir);
			}
			else if (!strcmp(argv[i], "--library"))
			{
				#include "movef.c"

				saPush(&settings->libs, argv[i]);

				printf("\x1b[32mLibrary\x1b[39m      ┃ %s\n", settings->libs.items[settings->libs.size-1]);
			}
			else
			{
				goto error;
			}
		}
		// char parameter
		else if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
				case 'i':
					#include "movef.c"

					saPush(&settings->incDirs, argv[i]);

					printf("\x1b[32mInclude Path\x1b[39m ┃ %s\n", settings->incDirs.items[settings->incDirs.size-1]);

					break;
				case 's':
					#include "movef.c"

					saPush(&settings->srcDirs, argv[i]);

					printf("\x1b[32mSource Path\x1b[39m  ┃ %s\n", settings->srcDirs.items[settings->srcDirs.size-1]);

					break;
				case 'l':
					#include "movef.c"

					saPush(&settings->libs, argv[i]);

					printf("\x1b[32mLibrary\x1b[39m      ┃ %s\n", settings->libs.items[settings->libs.size-1]);

					break;
				case 'v':
					#include "movef.c"
					
					settings->version = (char*)realloc(settings->version, (strlen(argv[i])+1)*sizeof(char));
					strcpy(settings->version, argv[i]);
					
					printf("\x1b[32mVersion\x1b[39m      ┃ %s\n", settings->version);

					break;
				case 'n':
					#include "movef.c"

					settings->name = (char*)realloc(settings->name, (strlen(argv[i])+1)*sizeof(char));
					strcpy(settings->name, argv[i]);
					
					printf("\x1b[32mName\x1b[39m         ┃ %s\n", settings->name);

					break;
				case 'o':
					#include "movef.c"

					settings->objDir = (char*)realloc(settings->objDir, (strlen(argv[i])+1)*sizeof(char));
					strcpy(settings->objDir, argv[i]);
					
					printf("\x1b[32mObject Path\x1b[39m  ┃ %s\n", settings->objDir);

					break;
				case 'b':
					#include "movef.c"

					settings->binDir = (char*)realloc(settings->binDir, (strlen(argv[i])+1)*sizeof(char));
					strcpy(settings->binDir, argv[i]);
					
					printf("\x1b[32mBinary Path\x1b[39m  ┃ %s\n", settings->binDir);

					break;
				case 'f':
					#include "movef.c"

					saPush(&settings->flags, argv[i]);

					printf("\x1b[32mFlags\x1b[39m        ┃ %s\n", settings->flags.items[settings->flags.size-1]);

					break;
				case 'p':
					#include "movef.c"

					saPush(&settings->libDirs, argv[i]);

					printf("\x1b[32mLibrary Path\x1b[39m ┃ %s\n", settings->libDirs.items[settings->libDirs.size-1]);

					break;
				default:
					goto error;
			}
		}
		// IDK
		else
		{
			goto error;
		}

		continue;

		error:
			printf("\x1b[33mWARNING\x1b[39m      ┃ Unknown option \x1b[32m%s\n", argv[i]);

			continue;
	}

	return 0;
}
