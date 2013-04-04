#include "Optlib.h"
#include "stdlib.h"
#include "string.h"
#include "stdarg.h"
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

int get_uint(FILE * stream)
{
    char tmp = 'a';
    char buff[10];
    int i = 0, output = 0;
    fgets(buff, 8, stream);
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

char _fgets(char *target, int length, FILE * source)
{
    int i = 0;
    fflush(stdin);
    fgets(target, length, source);
    while (*(target + i) != '\n' && *(target + i))
        i++;
    if (*(target + i) == '\n' && i)
        *(target + i) = '\0';
    return *(target);
}

char *fget_str(FILE * file, int length, char stop_character,
               int excl_char_num, ...)
{
    int i = 0, j = 0, exclude_char = 0;
    char tmp;
    char *str;
    char *excl_chars;
    va_list args;
    excl_chars = (char *) calloc(excl_char_num + 1, sizeof(char));
    str = (char *) calloc(length + 1, sizeof(char));
    va_start(args, excl_char_num);
    for (i = 0; i < excl_char_num; i++)
        excl_chars[i] = va_arg(args, char);
    va_end(args);
    i = 0;
    while (i < length) {
        tmp = getc(file);
        if (tmp == stop_character)
            break;
        for (j = 0; j < excl_char_num; j++)
            if (excl_chars[j] == tmp)
                exclude_char = 1;
        if (exclude_char) {
            exclude_char = 0;
            continue;
        }
        str[i] = tmp;
        i++;
    }
    free(excl_chars);
    return str;
}
