#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "prototypes.c"


/**
 * handle_file_input - Handles input from a file instead of stdin
 * @filename: Name of the file to read from
 * @av: Argument vector passed to main
 *
 * Return: Always 0 on success
 */

void handle_file_input(const char *filename, char **av)
{
	char *line = NULL;
	size_t len = 0;
	FILE *file = fopen(filename, "r");

	(void)av;
	if (file == NULL)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	while (getline(&line, &len, file) != -1)
	{
		size_t line_length = strlen(line);

		if (line_length > 0 && line[line_length - 1] == '\n')
		{
			line[line_length - 1] = '\0';
		}
		trim_input(line);
		if (strlen(line) > 0)
		{
			execute_command(parse_input(line), av);
		}
		/* Free memory*/
		free(line);
		line = NULL;
		len = 0;
	}
	fclose(file);
}
