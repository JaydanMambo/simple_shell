#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "prototypes.c"

/**
 * main - Simple shell program
 *
 * Return: Always 0.
 */

int main(void)
{
	char *input = NULL;
	size_t input_size = 0;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		getline(&input, &input_size, stdin);
		char **command = parse_input(input);

		execute_command(command);
		free(command);
	}
	free(input);
	return (0);

}
