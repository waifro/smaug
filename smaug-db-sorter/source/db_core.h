#ifndef DB_CORE_H
#define DB_CORE_H

#include <dirent.h>

//extern DIR *dbcore_rootdir;
extern char dbcore_startf[512];

int DBCORE_SliceData(char *src);
int DBCORE_StartSequence(char *ptr);

int DBCORE_CompareParameterString(char *ptr, char *foo);
int DBCORE_CompareMultipleParam(char *ptr, int index_start, char *foo);

int DBCORE_SanitizeString(char *ptr, short int index);
int DBCORE_CheckStringStatus(char *foo);

#endif
