#ifndef PROTOTYPES_C
#define PROTOTYPES_C

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


/* Custom string functions */
char *custom_strcpy(char *dest, const char *src);
char *custom_strcat(char *dest, const char *src);
int custom_strcmp(const char *s1, const char *s2);

/* Other function prototypes */
char **parse_input(char *input);
void execute_command(char **command, char **av);


#endif /* PROTOTYPES_C */
