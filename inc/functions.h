#ifndef __HD_FUNCTIONS_H__
#define __HD_FUNCTIONS_H__

#include <msap.h>
#include "structures.h"

int    getFiles      (char*, sa*);
int    getSettings   (struct hd_settings*, int, char**);
int    runChecks     (struct hd_settings*);
int    openFiles     (struct hd_settings, struct hd_file**);
int    genHead       (char**, struct hd_settings);
char * includeSearch (char*, struct hd_settings);
int    genBody       (char**, struct hd_settings, struct hd_file*);

#endif
