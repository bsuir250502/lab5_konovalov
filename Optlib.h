#include "stdio.h"
#ifndef _WIN32
#include "stdio_ext.h"
#define  fflush __fpurge
#endif
#ifndef OPTLIB_H
int getopt_c(char *, int);
int get_uint(FILE *);
char _fgets(char *, int, FILE *);
char *fget_str(FILE *, int, char, int, ...);
#endif
