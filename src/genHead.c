#include "structures.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int genHead (char **makefile, struct hd_settings s)
{
	size_t size = 1314;
	*makefile = (char*)malloc(size * sizeof(char));

	register size_t i;

	// INC
	strcpy(*makefile, "# Flags\nINC     = ");

	for (i = 0; i<s.incDirs.size; i++)
	{
		// resize to fit include
		size += strlen(s.incDirs.items[i])+3;
		*makefile = (char*)realloc(*makefile, size * sizeof(char));
	
		// add include
		strcat(*makefile, "-I");
		strcat(*makefile, s.incDirs.items[i]);
		strcat(*makefile, " ");
	}

	// LIB
	strcat(*makefile, "\nLIB     = ");

	for (i = 0; i<s.libDirs.size; i++)
	{
		// resize to fit include
		size += strlen(s.libDirs.items[i])+3;
		*makefile = (char*)realloc(*makefile, size * sizeof(char));
	
		// add include
		strcat(*makefile, "-L");
		strcat(*makefile, s.libDirs.items[i]);
		strcat(*makefile, " ");
	}

	// LIBS
	strcat(*makefile, "\nLIBS    = ");

	for (i = 0; i<s.libs.size; i++)
	{
		// resize to fit include
		size += strlen(s.libs.items[i])+3;
		*makefile = (char*)realloc(*makefile, size * sizeof(char));
	
		// add include
		strcat(*makefile, "-l");
		strcat(*makefile, s.libs.items[i]);
		strcat(*makefile, " ");
	}

	// Flags
	strcat(*makefile, "\nCFLAGS  = ");

	for (i = 0; i<s.flags.size; i++)
	{
		// resize to fit include
		size += strlen(s.flags.items[i])+1;
		*makefile = (char*)realloc(*makefile, size * sizeof(char));
	
		// add include
		strcat(*makefile, s.flags.items[i]);
		strcat(*makefile, " ");
	}

	strcat(*makefile, "\nCFLAGS += ${INC} ${LIB} ${LIBS}\n");

	// OBJ
	strcat(*makefile, "\n# directories\nOBJ     = ");
	strcat(*makefile, s.objDir);

	// BIN
	strcat(*makefile, "\nBIN     = ");
	strcat(*makefile, s.binDir);

	// binary info
	strcat(*makefile, "\n\n#binary info");

	// NAME
	strcat(*makefile, "\nNAME    = ");
	strcat(*makefile, s.name);

	// VERSION
	strcat(*makefile, "\nVERSION = ");
	strcat(*makefile, s.version);

	// presets
	strcat(*makefile, "\
\n\
# presets\n\
OUT = ${NAME}\n\
# test out ${NAME}-${VER}_test\n\
CC  = cc ${CFLAGS}\n\
\n\
\n\
# build test\n\
all: message ${OUT}\n\
	printf \"\\x1b[1;32m━━━SUCCESS━━━┛ Created Binary\\x1b[0m\\n\"\n\
\n\
# build release\n\
build: message clean_part ${OUT}\n\
	strip -s ${OUT}\n\
	printf \"\\x1b[1;32m━━━SUCCESS━━━┛ \\x1b[39mRelase build\\x1b[0m\\n\"\n\
\n\
# clean section\n\
clean_part:\n\
	rm ${BIN}/* ${OBJ}/* -f\n\
	printf \"\\x1b[1;35m━━━CLEANED━━━┫\\x1b[0m\\n\"\n\
\n\
# clean\n\
clean: message clean_part\n\
	printf \"\\x1b[1;32m━━━SUCCESS━━━┛\\x1b[0m\\n\"\n\
\n\
\n\
# generate new makefile\n\
gen: message clean_part\n\
	hd ");

strcat(*makefile, "\n\
	printf \"\\x1b[1;32m━━━SUCCESS━━━┛ Create new\\x1b[35m MakeFile \\x1b[0m\\n\"\n\
\n\
# print settings\n\
message:\n\
	printf \"\\x1b[1;35m%s \\x1b[39mV%s\\n\" ${NAME} ${VER}\n\
	printf \"\\x1b[1;39mMakefile generated from \\x1b[35mHD\\x1b[39m\\n\"\n\
	printf \"\\x1b[39m ━ \\x1b[1;39mUnder the \\x1b[32mMimik License 1.0\\n\"\n\
	printf \"\\x1b[39m ━ \\x1b[1;32mCopyright (c) 2022 Noah Arcouette\\x1b[0m  ┃\\n\"\n\
	printf \"\\x1b[39m━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━┛\\n\"\n\
\n\
ifndef VERBOSE\n\
.SILENT:\n\
endif\n\
\n\
");

	return 0;
}

/*
gen: message clean_part
	hd <options>
*/

