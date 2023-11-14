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
 * @environ: The environment variables
 * Return: Always 0 on success
*/
int main(int ac, char **av, char **environ)
{
	char *input = NULL;
	char *input_copy = NULL;
	size_t input_size = 0;
	char **command;
	char **commands;
	int i;
	bool interactive_mode = isatty(STDIN_FILENO);
	/*char **env = environ; */
	
	if (ac == 2)
	{
		handle_file_input(av[1], av);
		return (0);
	}
	else if (ac > 2)
	{
		fprintf(stderr, "Usage: %s [filename]\n", av[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
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
			trim_input(input);
			if (contains_logical_operator(input, "&&"))
			{
				execute_command_with_and(input, av);
			}
			else if (contains_logical_operator(input, "||")) 
			{
				execute_command_with_or(input, av);
			}
			else if (strchr(input, ';') != NULL)
			{
				input_copy = strdup(input);
				commands = parse_commands_separated_by_semicolon(input_copy);
				
				i = 0;
				while(commands[i] != NULL) {
					command = parse_input(commands[i]);
					execute_command(command, av);
					free(command);				
					i++;
				}
				free(commands);
				free(input_copy);

				
			}
			else
			{
			command = parse_input(input);
					
				if (command != NULL)
				{
				if (IS_EXIT_COMMAND(command))
					handle_exit_command(command);
				else if (IS_ENV_COMMAND(command, environ))
					custom_env(ac, av, environ);
				else if (IS_SETENV_COMMAND(command))
					handle_setenv_command(command);
				else if (IS_UNSETENV_COMMAND(command))
					unsetenv_builtin(command);
				else if(strcmp(command[0], "cd") == 0)
					cd_command(command, av);
				else if (strncmp(input, "alias", 5) == 0)
				{
					alias_command(command, av);
				}
				else
				{
					execute_command(command, av);
				}
				free(command);
				}
			}
		
			free(input);
			input = NULL;
			input_size = 0;
			display_prompt(interactive_mode);
		}
		free(input);
	}
	
	return (0);
}
