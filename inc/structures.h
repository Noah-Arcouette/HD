#ifndef __HG_SETTINGS_H__
#define __HD_GET_FILES_H__

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

	char *name;    // add application name
	char *version; // add version to application
};

struct hd_file
{
	char *path;
	sa    files;
};

#endif
