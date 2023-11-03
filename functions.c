#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "prototypes.c"
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

	token = strtok(input, "\t\n ");
	while (token != NULL)
	{
		command[i] = token;
		token = strtok(NULL, "\t\n ");
		i++;
	}
	command[i] = NULL;

	return (command);

}

/**
 * execute_command - Execute a command and wait for the child process to finish
 *
 * @command: An array of strings containing the command and arguments.
 * @av: from arguemnts
*/

void execute_command(char **command, char **av)
{
	pid_t child_pid;
	int status;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror(av[0]);
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if (execve(command[0], command, NULL) == -1)
		{
			perror(av[0]);
		}
	}
	else
	{
		wait(&status);
	}

}
