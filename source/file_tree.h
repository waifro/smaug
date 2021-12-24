#ifndef FILE_TREE_H
#define FILE_TREE_H

FILE *FILE_OpenFile(char *pathfile);
int FILE_CloseFile(FILE *stream);
int FILE_ReadFile(FILE *stream, char *strout);

int FILE_WriteOutput(const char *strin);

#endif
