#ifndef __HD_STRUCTURES_H__
#define __HD_STRUCTURES_H__

#include <msap.h>

struct hd_settings
{
	sa srcDirs; // to open files for reading
	sa incDirs; // to check if include exist
	sa libDirs; // to add to flags
	sa libs;    // to add to flags
	sa flags;   // to add to flags

	char *binDir; // to output binary
	char *objDir; // to output objects

	char *name;     // set application name
	char *version;  // set version to application
	char *makefile; // set makefile / output file name
};

struct hd_file
{
	char *path;
	sa    files;
	int   term:2; // terminator
};

#endif
