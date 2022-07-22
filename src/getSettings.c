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
	int argc, 
	char** argv
)
{	
	printf("\x1b[1m");

	for (register int i = 1; i<argc; i++)
	{
		// string parameter
		if (argv[i][0] == '-' && argv[i][1] == '-')
		{
			if (!strcmp(argv[i], "--version"))
			{
				goto o_version;	
			}
			else if (!strcmp(argv[i], "--config"))
			{
				goto o_config;
			}
			else if (!strcmp(argv[i], "--makefile"))
			{
				goto o_makefile;
			}
			else if (!strcmp(argv[i], "--include"))
			{
				goto o_include;
			}
			else if (!strcmp(argv[i], "--source"))
			{
				goto o_source;
			}
			else if (!strcmp(argv[i], "--name"))
			{
				goto o_name;
			}
			else if (!strcmp(argv[i], "--flag"))
			{
				goto o_flag;
			}
			else if (!strcmp(argv[i], "--path"))
			{
				goto o_path;
			}
			else if (!strcmp(argv[i], "--object"))
			{
				goto o_object;
			}
			else if (!strcmp(argv[i], "--binary"))
			{
				goto o_binary;
			}
			else if (!strcmp(argv[i], "--library"))
			{
				goto o_library;
			}
			else if (!strcmp(argv[i], "--help"))
			{
				goto help;
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
				case 'c':
					goto o_config;
				case 'h':
					goto help;
				case 'm':
					goto o_makefile;
				case 'i':
					goto o_include;
				case 's':
					goto o_source;
				case 'l':
					goto o_library;
				case 'v':
					goto o_version;
				case 'n':
					goto o_name;
				case 'o':
					goto o_object;
				case 'b':
					goto o_binary;
				case 'f':
					goto o_flag;
				case 'p':
					goto o_path;
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

		o_config:
			#include "movef.c"

			printf("\x1b[35mConfig      \x1b[39m ┃ %s\n", argv[i]);

			if (useConfig(argv[i], settings))
			{
				return 1;
			}

			printf("\x1b[35mCommand Line \x1b[39m┃\n");

			continue;

		o_include:
			#include "movef.c"

			saPush(&settings->incDirs, argv[i]);

			printf("\x1b[32mInclude Path\x1b[39m ┃ %s\n", settings->incDirs.items[settings->incDirs.size-1]);

			continue;

		o_source:
			#include "movef.c"

			saPush(&settings->srcDirs, argv[i]);

			printf("\x1b[32mSource Path\x1b[39m  ┃ %s\n", settings->srcDirs.items[settings->srcDirs.size-1]);

			continue;

		o_binary:
			#include "movef.c"

			settings->binDir = (char*)realloc(settings->binDir, (strlen(argv[i])+1)*sizeof(char));
			strcpy(settings->binDir, argv[i]);
			
			printf("\x1b[32mBinary Path\x1b[39m  ┃ %s\n", settings->binDir);

			continue;

		o_object:
			#include "movef.c"

			settings->objDir = (char*)realloc(settings->objDir, (strlen(argv[i])+1)*sizeof(char));
			strcpy(settings->objDir, argv[i]);
			
			printf("\x1b[32mObject Path\x1b[39m  ┃ %s\n", settings->objDir);

			continue;

		o_library:
			#include "movef.c"

			saPush(&settings->libs, argv[i]);

			printf("\x1b[32mLibrary\x1b[39m      ┃ %s\n", settings->libs.items[settings->libs.size-1]);

			continue;

		o_path:
			#include "movef.c"

			saPush(&settings->libDirs, argv[i]);

			printf("\x1b[32mLibrary Path\x1b[39m ┃ %s\n", settings->libDirs.items[settings->libDirs.size-1]);

			continue;

		o_flag:
			#include "movef.c"

			saPush(&settings->flags, argv[i]);

			printf("\x1b[32mFlag \x1b[39m        ┃ %s\n", settings->flags.items[settings->flags.size-1]);

			continue;

		o_name:
			#include "movef.c"

			settings->name = (char*)realloc(settings->name, (strlen(argv[i])+1)*sizeof(char));
			strcpy(settings->name, argv[i]);
			
			printf("\x1b[32mName\x1b[39m         ┃ %s\n", settings->name);

			continue;

		o_version:
			#include "movef.c"
					
			settings->version = (char*)realloc(settings->version, (strlen(argv[i])+1)*sizeof(char));
			strcpy(settings->version, argv[i]);
			
			printf("\x1b[32mVersion\x1b[39m      ┃ %s\n", settings->version);

			continue;

		o_makefile:
			#include "movef.c"
					
			settings->makefile = (char*)realloc(settings->makefile, (strlen(argv[i])+1)*sizeof(char));
			strcpy(settings->makefile, argv[i]);
			
			printf("\x1b[32mMakeFile\x1b[39m     ┃ %s\n", settings->makefile);

			continue;

		error:
			printf("\x1b[31mERROR\x1b[39m        ┃ Unknown option \x1b[32m%s\n", argv[i]);

			// return 1;

		help:
			puts("\x1b[1;39m━━━━━━━━━━━━━┻━━━━━┓\n\x1b[35mHelp\x1b[39m               ┃\n━━━━━━━━━━━━━━━━━━━┫\n\
\x1b[32m━━include, ━i      \x1b[39m┃ Add include directory\n\
\x1b[32m━━source, ━s       \x1b[39m┃ Add source directory\n\
\x1b[32m━━binary, ━b       \x1b[39m┃ Set binary directory\n\
\x1b[32m━━object, ━o       \x1b[39m┃ Set object directory\n\
\x1b[32m━━library, ━l      \x1b[39m┃ Add library\n\
\x1b[32m━━path, ━p         \x1b[39m┃ Add library path\n\
\x1b[32m━━flag, ━f         \x1b[39m┃ Add C flag\n\
\x1b[32m━━name, ━n         \x1b[39m┃ Set project / binary name\n\
\x1b[32m━━version, ━v      \x1b[39m┃ Set project / binary version\n\
\x1b[32m━━makefile, ━m     \x1b[39m┃ Set makefile / output name\n\
\x1b[32m━━help, ━h         \x1b[39m┃ Show help message\n\
\x1b[32m━━config, ━c       \x1b[39m┃ Use configuration file\n\
━━━━━━━━━━━━━┳━━━━━┛\
");

			return 1;
	}

	return 0;
}
