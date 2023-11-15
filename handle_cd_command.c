#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "prototypes.c"

/**
 * cd_command - Change the current directory of the process
 * @command: An array of strings containing the command and arguments.
 * @av: Argument vector.
 */

void cd_command(char **command, char **av)
{
	char *directory = command[1];
	char *current_directory;

	if (directory == NULL)
	{
		directory = custom_getenv("HOME");
	}
	if (strcmp(directory, "-") == 0)
	{
		directory = custom_getenv("OLDPWD");
	}
	current_directory = custom_getcwd(NULL, 0);

	if (chdir(directory) == 0)
	{
		/* Update the environment variable PWD */
		setenv("PWD", custom_getcwd(NULL, 0), 1);
		/*Update the environment variable OLDPWD with the previous directory*/
		setenv("OLDPWD", current_directory, 1);
	}
	else
	{
		fprintf(stderr, "%s: 1: cd: can't cd to %s\n", av[0], directory);
	}
	free(current_directory);
}

/**
 * custom_getcwd - Get the current working directory
 * @buffer: A buffer to store the current working directory.
 * @size: The size of the buffer.
 *
 * Return: On success, returns the current working directory.
 *			On failure, returns NULL and prints an error message.
 */
char *custom_getcwd(char *buffer, size_t size)
{
	if (buffer == NULL)
	{
		size = 1024;
		buffer = malloc(size);
		if (buffer == NULL)
		{
			perror("Unable to allocate buffer for getcwd");
			exit(EXIT_FAILURE);
		}

	}
	while (1)
	{
		if (getcwd(buffer, size) != NULL)
		{
			return (buffer);
		}

		if (errno != ERANGE)
		{
			perror("getcwd() failed");
			free(buffer);
			return (NULL);
		}

		size *= 2; /* Doubling the size for getcwd() */
		buffer = realloc(buffer, size);
		if (buffer == NULL)
		{
			perror("cd");
			free(buffer);
			exit(EXIT_FAILURE);
		}
	}
}
