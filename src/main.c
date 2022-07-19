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
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n"
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

	printf("\x1b[1;35mSettings\x1b[0m  ┃\n━━━━━━━━━━┛\n");

	// read command line parameters into a settings structure
	if (getSettings(&settings, (size_t)argc, argv))
	{
		printf("\n\x1b[1;31m━━━━CRASH━━━━\x1b[0m\n");

		crash = 1;
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

	return crash;
}
