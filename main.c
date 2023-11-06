#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "prototypes.c"

/**
 * display_prompt - Display a prompt for input in interactive mode
 * @interactive_mode: Interactive mode flag
*/
void display_prompt(bool interactive_mode)
{
	if (interactive_mode)
	{
		write(STDOUT_FILENO, "($) ", 4);
	}
}

/**
 * main - Simple shell program
 * @ac: The argument count
 * @av: The argument vector
 * Return: Always 0 on success
*/
int main(int ac, char **av)
{
	char *input = NULL;
	size_t input_size = 0;
	char **command;
	bool interactive_mode = isatty(STDIN_FILENO);

	(void)ac;
	display_prompt(interactive_mode);
	while (custom_getline(&input, &input_size, STDIN_FILENO) != -1)
	{
		if (feof(stdin))
		{
			free(input);
			if (interactive_mode)
			{
				write(STDOUT_FILENO, "\n", 1);
			}
			break;
		}
		if (input[0] == '\n')
		{
			display_prompt(interactive_mode);
			continue;
		}
		command = parse_input(input);
		execute_command(command, av);
		free(command);
		free(input);
		input = NULL;
		input_size = 0;
		display_prompt(interactive_mode);
	}
	free(input);
	return (0);
}
