#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
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
	bool interactive_mode = isatty(STDIN_FILENO);

	(void)ac;
	if (interactive_mode)
	{
		write(STDOUT_FILENO, "($) ", 4);
	}
	while (getline(&input, &input_size, stdin) != -1)
	{
		if (feof(stdin))
		{
			if (interactive_mode)
			{
				write(STDOUT_FILENO, "\n", 1);
			}
			break;
		}
		command = parse_input(input);
		execute_command(command, av);
		if (!interactive_mode)
		{
			free(input);
			input = NULL;
			input_size = 0;
		}
		if (interactive_mode)
		{
			write(STDOUT_FILENO, "($) ", 4);
		}
	}
	free(input);
	free(command);
	return (0);
}

