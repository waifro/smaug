#ifndef FILE_OPERATE_H
#define FILE_OPERATE_H

int FILE_OpenFile(FILE *stream, char *pathfile);
int FILE_CloseFile(FILE *stream);
int FILE_ReadFile(FILE *stream, char *strout);

#endif
