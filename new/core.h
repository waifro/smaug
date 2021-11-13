#ifndef CORE_H
#define CORE_H

int CORE_OpenFile(FILE *stream, char *pathfile);
int CORE_CloseFile(FILE *stream);
int CORE_ReadFile(FILE *stream, char *strout);
int CORE_SearchString(char *strin, char *buffer);

void CORE_StartSequence(int argc, char *argv[]);

#endif
