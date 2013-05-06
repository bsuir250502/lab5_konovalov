#include "optlib.h"
#include "stdlib.h"
#include "string.h"
#include "stdarg.h"
#define OPTLIB_H 1

int getopt_c(char* arg,int hyphen_lim)    /* hyphen = - */
{
	int arg_type=0,i=1;
	while (*arg=='-' && hyphen_lim--)
	{
		arg_type++;
		*(arg)=*(arg+1);
		while (*(arg+i-1))
		{
			*(arg+i)=*(arg+i+1);
			i++;
		}
		i=1;
	}
	return arg_type;
}

int get_posint(int* target, FILE * stream)
{
    char buff[1000];
    int output = 0;
    char* check;
    printf ("Maximum 9 digit number\n");
    fgets_c(buff, 1000, stream);
    *target=strtol(buff,&check,10);
    if (*check!='\0' || strlen(buff)>9 || *target<0)
        output=-1;
    return output;
}

char fgets_c(char *target, int length, FILE * source)
{
    int i = 0;
    char buf[1000];
    fgets(buf, 1000, source);
    strncpy(target,buf,length-1);
    target[length-1]='\0';
    if (strlen(buf)>length)
        printf("String you entered was too long, data is partially lost.\n");
    while (target[i] != '\n' && target[i])
        i++;
    if (target[i] == '\n' && i)
        target[i] = '\0';
    return *target;
}

int fget_str(FILE* file,char* str,int length,char stop_character,int excl_char_num,...)
{
	int i=0,j=0,exclude_char=0;
	char tmp;
	char* excl_chars;
	va_list args;
	excl_chars=(char*)calloc(excl_char_num+1,sizeof(char));
	va_start(args,excl_char_num);
	for (i=0;i<excl_char_num;i++)
		excl_chars[i]=va_arg(args,char);
	va_end(args);
	i=0;
	while (i<length-1)
	{
		tmp=getc(file);
		if (tmp==stop_character)
			break;
		for (j=0;j<excl_char_num;j++)
			if (excl_chars[j]==tmp)
				exclude_char=1;
		if(exclude_char)
		{
			exclude_char=0;
			continue;
		}
		str[i]=tmp;
		i++;
	}
	str[i]='\0';
	free(excl_chars);
	return 1;
}