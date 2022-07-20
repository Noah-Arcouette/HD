#include "structures.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int genHead (char **makefile, struct hd_settings s)
{
	size_t size = 1149;
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

	// LIBS
	strcat(*makefile, "\nCFLAGS  = ");

	for (i = 0; i<s.flags.size; i++)
	{
		// resize to fit include
		size += strlen(s.flags.items[i])+3;
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

	return 0;
}

/*
sa srcDirs; // to open files for reading

char *binDir; // to output binary

# presets
OUT = ${NAME}
# test out ${NAME}-${VER}_test
CC  = cc ${CFLAGS}


# build test
all: message ${OUT}
	printf "\x1b[1;32m━━━SUCCESS━━━┛ Created Binary\x1b[0m\n"

# build release
build: message clean_part ${OUT}
	strip -s ${OUT}
	printf "\x1b[1;32m━━━SUCCESS━━━┛ \x1b[39mRelase build\x1b[0m\n"

# clean section
clean_part:
	rm ${BIN}/* ${OBJ}/* -f
	printf "\x1b[1;35m━━━CLEANED━━━┫\x1b[0m\n"

# clean
clean: message clean_part
	printf "\x1b[1;32m━━━SUCCESS━━━┛\x1b[0m\n"
	

# generate new makefile
gen: message clean_part
	hd <options>
	printf "\x1b[1;32m━━━SUCCESS━━━┛ Create new \x1b[35m MakeFile \x1b[0m\n"

# print settings
message:
	printf "\1b[1;35m%s \x1b[39mV%s\n" ${NAME} ${VER}
	printf "\x1b[1;39mMakefile generated from \x1b[35mHD\x1b[39m\n"
	printf "\x1b[39m ━ \x1b[1;39mUnder the \x1b[32mMimik License 1.0\n"
	printf "\x1b[39m ━ \x1b[1;32mCopyright (c) 2022 Noah Arcouette\x1b[0m  ┃\n"
	printf "\x1b[39m━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━┛\n"

ifndef VERBOSE
.SILENT:
endif

*/

