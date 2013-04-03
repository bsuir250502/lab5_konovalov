#include "Optlib.h"
#include "stdlib.h"
#include "string.h"
#define OPTLIB_H 1

int getopt_c(char *arg, int hyphen_lim)
{                               /* hyphen = - */
    int arg_type = 0, i = 1;
    while (*arg == '-' && hyphen_lim--) {
        arg_type++;
        *(arg) = *(arg + 1);
        while (*(arg + i - 1)) {
            *(arg + i) = *(arg + i + 1);
            i++;
        }
        i = 1;
    }
    return arg_type;
}

int get_num(void)
{
    char tmp = 'a';
    char buff[10];
    int i = 0, output = 0;
    fgets(buff, 8, stdin);
    if ((tmp = buff[i]) == '\n')
        return -1;
    do {
        if (tmp > '9' || tmp < '0')
            return -1;
        output = output * 10 + (tmp - '0');
        i++;
        tmp = buff[i];
    } while (tmp && tmp != '\n');
    return output;
}

void _fgets(char *target, int length, FILE * source)
{
    int i = 0;
    fflush(stdin);
    fgets(target, length, source);
    while (*(target + i) != '\n' && *(target + i))
        i++;
    if (*(target + i) == '\n' && i)
        *(target + i) = '\0';
    return;
}
