#ifndef __HD_GET_FILES_H__
#define __HD_GET_FILES_H__

#include <msap.h>

int  getFiles    (char*, sa*);
int  getSettings (struct hd_settings*, int, char**);
int  runChecks   (struct hd_settings*);
int  openFiles   (struct hd_settings, struct hd_file**);

#endif
