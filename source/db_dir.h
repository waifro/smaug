#ifndef DB_DIR_H
#define DB_DIR_H

// returns 27 - 28 if digit/symbol; (i) if character; -1 if error
int DBDIR_OperateFolder(char chr);

int DBDIR_CheckSortFolder(char chr);
int DBDIR_CheckAlphaStructure(char *ptr, char *result);

int DBDIR_CopyRootFolder(char *folder);
int DBDIR_CheckFolder(char *folder);
const char *DBDIR_CreateFolder(char *folder);

#endif
