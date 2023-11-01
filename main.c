#include "shell.c"

/**
 * display_prompt - Displays a shell prompt on stdout
 */

void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}

/**
 * read_command - Reads a command from user in the stdin
 *
 * Return: A dynamically allocated string with the command entered by user
*/

char *read_command(void)
{
	char *line = NULL;
	ssize_t read;
	size_t len = 0;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
	read = getline(&line, &len, stdin);
	if (read == -1)
	{
		free(line);
		exit(EXIT_SUCCESS);
	}
	return (line);
}

/**
 * execute_command - Executes the command entered by user
 *
 * @line: The command entered by the user
*/

void execute_command(char *line)
{
	/* Fork a child process */
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("Failed to fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		/* Child process */
		char *args[] = {line, NULL};

		execve(line, args, NULL);
		/* Executing command failed */
		perror(line);
		free(line);
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		int status;

		wait(&status);
	}
}

/**
 * main - Entry point for the shell program
 *
 * Return: Always 0
 */

int main(void)
{
	while (1)
	{
		char *line = read_command();

		execute_command(line);
		free(line);
	}
return (0);
}
