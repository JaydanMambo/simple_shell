#include "prototypes.c"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>

/**
 * contains_logical_operator - Check if input contains a logical operator
 * @input: The input string
 * @operator: The logical operator to check for
 * Return: true if input contains operator, false otherwise
*/
bool contains_logical_operator(const char *input, const char *operator)
{
    /* Use strstr to find the position of the operator in the input */
    char *operator_pos = strstr(input, operator);

    /* If operator is found, return true, else return false */
    return (operator_pos != NULL);
}

#include <stdio.h>
#include <stdlib.h>
#include "prototypes.c"

/**
 * parse_input_with_and - Parse input containing "&&" operator
 * @input: The input string
 * @av: The argument vector
 * Return: An array of strings containing the command and arguments.
 */
char **parse_input_with_and(char *input)
{
    char *token;
    char **commands = malloc(sizeof(char *) * 1024);
    int i = 0;

    if (commands == NULL)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, "&&");
    while (token != NULL)
    {
        commands[i] = token;
        token = strtok(NULL, "&&");
        i++;
        
    }

    if (i == 0)
    {
        free(commands);
        
        return NULL;
    }

    commands[i] = NULL;
    

    return (commands);
}



/**
 * execute_command_with_and - Execute a command with && operator
 * @input: The input string
 * @av: The argument vector
 */
void execute_command_with_and(char *input, char **av)
{
    char *input_copy = NULL;
	char **command;
	char **commands;
	int i, status;
    input_copy = strdup(input);
    
	commands = parse_input_with_and(input_copy);
    i = 0;
    
	while (commands[i] != NULL)
    {
        printf("commands %d is: %s\n", i, commands[i]);
        command = parse_input(commands[i]);
		printf("Command %d is: %s\n", i, command[i]);
		execute_command(command, av);
        printf("Command %d exited with status %d\n", i, WEXITSTATUS(status));
        
        /* Check the exit status of the command */
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            /* If the command fails, stop executing further commands */
            break;
        }
		free(command);
		i++;
	}
	free(commands);
	free(input_copy);
}
