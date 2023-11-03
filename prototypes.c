#ifndef PROTOTYPES_C
#define PROTOTYPES_C

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


char **parse_input(char *input);
void execute_command(char **command, char **av);

#endif /* PROTOTYPES_C */
