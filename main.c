#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "prototypes.c"


/**
 * main - Simple shell program
 *
 * @ac: arguments
 * @av: array of arguments
 * Return: Always 0.
 */

int main(int ac, char **av)
{
	char *input = NULL;
	size_t input_size = 0;
	char **command;
	ssize_t read_result;

	(void)ac;
	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		read_result = getline(&input, &input_size, stdin);
		if (read_result == -1)
		{
			break;
		}
		if (input[0] == '\n')
		{
			continue;
		}
		command = parse_input(input);
		execute_command(command, av);
		free(command);
	}

	free(input);

	return (0);

}
