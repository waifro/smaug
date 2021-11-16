#ifndef FILE_OPERATE_H
#define FILE_OPERATE_H

FILE *FILE_OpenFile(char *pathfile);
int FILE_CloseFile(FILE *stream);
int FILE_ReadFile(FILE *stream, char *strout);

#endif
