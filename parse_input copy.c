#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "prototypes.c"
#include <string.h>

/**
 * parse_input - Splits the input into tokens/arguments
 *
 * @input: User input as a string
 *
 * Return: An array of strings containing the command and arguments.
*/

char **parse_input(char *input)
{
	char *token;
	char **command = malloc(sizeof(char *) * 1024);
	int i = 0;

	if (command == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}

	token = custom_strtok(input, "\t\n ");
	while (token != NULL)
	{
		if (token[0] == '#')
			break;
		if (strcmp(token, "$?") == 0)
		{
			char exit_status_str[2];

			snprintf(exit_status_str, sizeof(exit_status_str), "%d", WEXITSTATUS(get_child_exit_status()));
			command[i] = strdup(exit_status_str);
		}
		else if (strcmp(token, "$$") == 0)
		{
			char pid_str[10];

			snprintf(pid_str, sizeof(pid_str), "%d", getpid());
			command[i] = strdup(pid_str);
		}
		else if(strcmp(token, "$PATH") == 0)
		{
			char *path = custom_getenv("PATH");
			command[i] = strdup(path);
		}
		else
		{
			command[i] = token;
		}
		token = custom_strtok(NULL, "\t\n ");
		i++;
	}
	/* Free token here?*/
	if (i == 0)
	{
		free(command);
		return (NULL);
	}
	command[i] = NULL;

	return (command);

}

/**
 * trim_input - Remove leading and trailing spaces and tabs from a string.
 * @str: The string to trim.
 */
void trim_input(char *str)
{
	int i, j;
	int len = custom_strlen(str);

    /* Trim leading spaces */
	i = 0;

	while (str[i] == ' ' || str[i] == '\t')
	{
		i++;
	}

    /* Shift the string to remove leading spaces */
	if (i > 0)
	{
		for (j = 0; j < len - i + 1; j++)
		{
			str[j] = str[i + j];
		}
	}

	len = custom_strlen(str);  /* Recalculate the string length */

    /* Trim trailing spaces */
	i = len - 1;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
	{
		str[i] = '\0';
		i--;
	}
}

/**
 * parse_commands_separated_by_semicolon - Splits the input into commands separated by ';'
 *
 * @input: User input as a string
 *
 * Return: An array of strings containing the commands.
 */
char **parse_commands_separated_by_semicolon(char *input)
{
    char *token;
    char **commands = malloc(sizeof(char *) * 1024);
    int i = 0;

    if (commands == NULL)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    token = custom_strtok(input, ";");
    while (token != NULL)
    {
		commands[i] = token;
		token = custom_strtok(NULL, ";");
		i++;
    }
    if (i == 0)
    {
        free(commands);
        return NULL;
    }
    commands[i] = NULL;
	

    return commands;
}
