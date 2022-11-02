#include <stdio.h>
#include "info.h"
#include <macsv.h>
#include <stdlib.h>
#include <msap.h>
#include <string.h>
#include "structures.h"
#include "info.h"
#include "functions.h"

int main (int argc, char **argv)
{
	int crash = 0;

	printf(
"\x1b[1;35mHD\x1b[39m V" VER "-" REV "\n\
Under the \x1b[32mMimik License 1.0\n\
Copyright (c) 2022 Noah Arcouette\n\
\x1b[39mThis is free and open source software;\n\
see the \x1b[32mMimik License 1.0\x1b[39m for copying conditions.\n\
The \x1b[32mMimik License 1.0\x1b[39m does not provide warranty of any kind.\x1b[0m  ┃\n\
━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n"
);

	// set empty settings
	struct hd_settings settings;
	settings.srcDirs.items = NULL;
	settings.srcDirs.size  = 0;
	settings.incDirs.items = NULL;
	settings.incDirs.size  = 0;
	settings.libDirs.items = NULL;
	settings.libDirs.size  = 0;
	settings.libs.items = NULL;
	settings.libs.size  = 0;
	settings.flags.items = NULL;
	settings.flags.size  = 0;

	settings.binDir  = NULL;
	settings.objDir  = NULL;

	settings.name    = NULL;
	settings.version = NULL;

	settings.makefile = NULL;

	printf("\x1b[1;35mSettings\x1b[0m     ┃\n━━━━━━━━━━━━━┫\n");

	// read command line parameters into a settings structure
	if (getSettings(&settings, (size_t)argc, argv))
	{
		printf("\x1b[1;31m━━━CRASHED━━━┛\x1b[0m\n");

		crash = 1;
	}
	else
	{
		printf("\x1b[39m━━━━━━━━━━━━━┫\n\x1b[1;35mChecking\x1b[0m     ┃\n━━━━━━━━━━━━━┫\n");

		// run checks
		if (runChecks(&settings))
		{
			printf("\x1b[1;31m━━━CRASHED━━━┛\x1b[0m\n");

			crash = 1;
		}
		else
		{
			printf("\x1b[39m━━━━━━━━━━━━━┫\n\x1b[1;35mParsing\x1b[0m      ┃\n━━━━━━━━━━━━━┫\n");

			struct hd_file *files;

			// open and split all include files
			if (openFiles(settings, &files))
			{
				printf("\x1b[1;31m━━━CRASHED━━━┛\x1b[0m\n");

				crash = 1;
			}
			else
			{
				printf("\x1b[39m━━━━━━━━━━━━━┫\n\x1b[1;35mGenerating\x1b[0m   ┃\n━━━━━━━━━━━━━┫\n");
			
				char *makefile = NULL;

				if (genHead(&makefile, settings))
				{
					printf("\x1b[1;31m━━━CRASHED━━━┛\x1b[0m\n");

					crash = 1;
				}
				else
				{
					printf("\x1b[1;32mGenerated    \x1b[39m┃ \x1b[35mMakefile \x1b[39mHead generated\x1b[0m\n");

					// makefile settings files
					if (genBody(&makefile, settings, files))
					{
						printf("\x1b[1;31m━━━CRASHED━━━┛\x1b[0m\n");

						crash = 1;
					}
					else
					{
						printf("\x1b[1;32mGenerated    \x1b[39m┃ \x1b[35mMakefile \x1b[39mBody generated\x1b[0m\n");

						FILE *fp = fopen(settings.makefile, "w");

						if (!fp)
						{
							printf("\x1b[31mCan not open \x1b[39m┃ \x1b[32m%s\n", settings.makefile);
						
							crash = 1;
						}
						else
						{
							fwrite(makefile, strlen(makefile), 1, fp);

							fclose(fp);
						}
					}
				}

				free(makefile);
			}

			register size_t files_i;
			for (files_i = 0; !files[files_i].term; files_i++)
			{
				free(files[files_i].path);
				saFree(files[files_i].files);
			}

			free(files);
		}
	}

	// free settings
	saFree(settings.srcDirs);
	saFree(settings.incDirs);
	saFree(settings.libDirs);
	saFree(settings.libs);
	saFree(settings.flags);

	free(settings.binDir);
	free(settings.objDir);
	free(settings.name);
	free(settings.version);

	if (!crash)
	{
		printf("\x1b[1;32m━━━SUCCESS━━━┛\x1b[0m\n");
	}

	return crash;
}
