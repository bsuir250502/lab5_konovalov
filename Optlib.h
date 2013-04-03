#include "stdio.h"
#ifndef _WIN32
#include "stdio_ext.h"
#define  fflush __fpurge
#endif
#ifndef OPTLIB_H
int getopt_c(char *, int);
int get_int(int *);
void _fgets(char *, int, FILE *);
#endif
