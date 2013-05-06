#include "stdlib.h"
#include "Optlib.h"   /* getopt_c */
#include "service.h"
#define SERVICE 1

int options(int argc,char** argv,char* file_path)
{
	const int hyphen_count=1;
	int no_arguments_needed=1,i=0,path_used=0;
	char* arg=NULL;
	for (i=1;i<argc;i++)
	{
		arg=*(argv+i);
		switch(getopt_c(arg,hyphen_count))
		{
			case 0:
				if (no_arguments_needed)
				{
					printf("Unknown command %s.\n",arg);
					return 0;
				}
				path_used=1;
				no_arguments_needed=1;
				break;
			case 1:
				if (no_arguments_needed==0)
					return 0;
				switch (*arg)
				{
					case 'h':
						no_arguments_needed=1;
						display_usage();
						return 'H';
						break;
					case 'l':
						no_arguments_needed=0;
						break;
					default:
						printf("Unknown command -%s.\n",arg);
						return 0;
						break;
				}
				break;
			default:
				printf("Unknown command %s.\n",arg);
				return 0;
				break;
		}
	}
	return path_used;
}

void display_usage(void)
{
	int i=0;
	char *help[]={"-h","-l <path>"}; 
	char *help_def[]={"Displays usage information",
		"Defines students list location"};
	printf ("Usage: lab5 [options]\n");
	for (i=0;i<2;i++)
		printf ("%-12s %s\n",help[i],help_def[i]);
	return;
}