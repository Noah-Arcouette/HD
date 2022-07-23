#include "structures.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int genHead (char **makefile, struct hd_settings s)
{
	size_t size = 1500;
	*makefile = (char*)malloc(size * sizeof(char));

	register size_t i;

	// INC
	strcpy(*makefile, "# Flags\nINC      = ");

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
	strcat(*makefile, "\nLIB      = ");

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
	strcat(*makefile, "\nLIBS     = ");

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
	strcat(*makefile, "\nDEFFLAGS = ");

	for (i = 0; i<s.flags.size; i++)
	{
		// resize to fit include
		size += strlen(s.flags.items[i])+1;
		*makefile = (char*)realloc(*makefile, size * sizeof(char));
	
		// add include
		strcat(*makefile, s.flags.items[i]);
		strcat(*makefile, " ");
	}

	strcat(*makefile, " ${INC}\n");

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

	if (s.mode == HD_MODE_STATIC)
	{
		strcat(*makefile, "\nLIBOUT = ${BIN}/${NAME}.a\n\n");
	}
	else if (s.mode == HD_MODE_DYNAMIC)
	{
		strcat(*makefile, "\nLIBOUT = ${BIN}/${NAME}.so\n\n");
	}

	// presets
	strcat(*makefile, "\
\n\
# presets\n\
OUT = ${BIN}/${NAME}\n\
# test out ${NAME}-${VER}_test\n\
CC  = cc\n\
\n\
\n\
# build test\n\
all: message ${OUT}\n\
	printf \"\\x1b[1;32m━━━SUCCESS━━━┛ Test Build\\x1b[0m\\n\"\n\
\n\
# build release\n");

	if (s.mode == HD_MODE_APP)
	{
		strcat(*makefile, "build: message clean_part ${OUT}\n\
	strip -s ${OUT}\n\
	printf \"\\x1b[1;32m━━━SUCCESS━━━┛ \\x1b[39mRelease Build\\x1b[0m\\n\"\n");
	}
	else
	{
		strcat(*makefile, "build: message clean_part ${LIBOUT}\n\
	printf \"\\x1b[1;32m━━━SUCCESS━━━┛ \\x1b[39mRelease Build\\x1b[0m\\n\"\n");
	}

	strcat(*makefile, "\
\n# clean section\n\
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
	printf \"\\x1b[1;39m━━━━━━━━━━━━━┛\\x1b[0m\\n\\n\"\n\
\n\
	hd ");

	// rebuild settings
	size += 
		strlen(s.name) + 4 + 
		strlen(s.version) + 4 +
		strlen(s.binDir) + 4 +
		strlen(s.objDir) + 4 +
		strlen(s.makefile) + 4;

	*makefile = (char*)realloc(*makefile, size * sizeof(char));
	strcat(*makefile, "-n ");
	strcat(*makefile, s.name);

	strcat(*makefile, " -v ");
	strcat(*makefile, s.version);

	strcat(*makefile, " -m ");
	strcat(*makefile, s.makefile);

	strcat(*makefile, " -b ");
	strcat(*makefile, s.binDir);

	strcat(*makefile, " -o ");
	strcat(*makefile, s.objDir);

	for (i = 0; i<s.srcDirs.size; i++)
	{
		size += strlen(s.srcDirs.items[i]) + 4;
		*makefile = (char*)realloc(*makefile, size * sizeof(char));
		
		strcat(*makefile, " -s ");
		strcat(*makefile, s.srcDirs.items[i]);
	}

	for (i = 0; i<s.incDirs.size; i++)
	{
		size += strlen(s.incDirs.items[i]) + 4;
		*makefile = (char*)realloc(*makefile, size * sizeof(char));
		
		strcat(*makefile, " -i ");
		strcat(*makefile, s.incDirs.items[i]);
	}

	for (i = 0; i<s.libDirs.size; i++)
	{
		size += strlen(s.libDirs.items[i]) + 4;
		*makefile = (char*)realloc(*makefile, size * sizeof(char));
		
		strcat(*makefile, " -p ");
		strcat(*makefile, s.libDirs.items[i]);
	}

	for (i = 0; i<s.libs.size; i++)
	{
		size += strlen(s.libs.items[i]) + 4;
		*makefile = (char*)realloc(*makefile, size * sizeof(char));
		
		strcat(*makefile, " -l ");
		strcat(*makefile, s.libs.items[i]);
	}

	for (i = 0; i<s.flags.size; i++)
	{
		size += strlen(s.flags.items[i]) + 4;
		*makefile = (char*)realloc(*makefile, size * sizeof(char));
		
		strcat(*makefile, " -f ");
		strcat(*makefile, s.flags.items[i]);
	}

	strcat(*makefile, "\n\
	printf \"\\x1b[1;32m\\n━━━━━━━━━━━━━┓\\nSUCCESS      ┃  \\x1b[39mCreate new\\x1b[35m MakeFile \\x1b[32m\\n━━━━━━━━━━━━━┛\\x1b[0m\\n\"\n\
\n\
# print settings\n\
message:\n\
	printf \"\\x1b[1;35m%s \\x1b[39mV%s\\n\" ${NAME} ${VERSION}\n\
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
