#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "prototypes.c"


/**
 * execute_command - Execute a command and wait for the child process to finish
 *
 * @command: An array of strings containing the command and arguments.
 * @av: from arguemnts
 * @exit_status: exit status of the last command
 * @pid: process ID of the shell
 *
*/

void execute_command(char **command, char **av)
{
	pid_t child_pid = fork();
	int status;

	if (child_pid == -1)
	{
		perror(av[0]);
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if (command == NULL || command[0] == NULL)
		{
			return;
		}
		if (access(command[0], X_OK) == 0)
		{
			execute_in_current_directory(command, av);
		}
		else
		{
			search_and_execute(command, av);
		}
		/* set_last_exit_status(WIFEXITED(status) ? WEXITSTATUS(status) : 1); */
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(child_pid, &status, 0);
		/* set_last_exit_status(WIFEXITED(status) ? WEXITSTATUS(status) : 1); */
		/*printf("The exit status of main is: %d\n", get_child_exit_status()); */
	}
}


/**
 * execute_in_current_directory - Execute command in current directory
 * @command: Command to execute
 * @av: Argument vector
 *
 * Return: pid_t of child process if successful, -1 otherwise
*/
void execute_in_current_directory(char **command, char **av)
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
		execve(command[0], command, NULL);

		perror(av[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(child_pid, &status, 0);
		set_child_exit_status(WIFEXITED(status) ? WEXITSTATUS(status) : 1);
		/*printf("The exit status is: %d\n", get_child_exit_status());*/
	}
}

/**
 * search_and_execute - Search PATH for command and execute if found
 * @command: Command to search for and execute
 * @av: Argument vector
 * @exit_status: Exit status of child process
 *
 * Return: pid_t of child process if successful, -1 otherwise
*/
void search_and_execute(char **command, char **av)
{
	char *path = custom_getenv("PATH");
	char *path_copy = custom_strdup(path);
	char *directory = custom_strtok(path_copy, ":");
	int command_found = 0;

	while (directory != NULL)
	{
		char command_path[1024];

		custom_strcpy(command_path, directory);
		custom_strcat(command_path, "/");
		custom_strcat(command_path, command[0]);

		if (access(command_path, X_OK) == 0)
		{
			execute_in_directory(command_path, command, av);
			command_found = 1;
			break;
		}
		directory = custom_strtok(NULL, ":");
	}

	free(path_copy);

	if (command_found == 0)
	{
		print_command_not_found(command[0], av[0]);
	}
}

/**
 * execute_in_directory - Execute command in given directory
 * @command_path: Full path to command to execute
 * @command: Command arguments
 * @av: Argument vector1
 *
*/
void execute_in_directory(char *command_path, char **command, char **av)
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

		execve(command_path, command, NULL);

		perror(av[0]);
		exit(EXIT_FAILURE);
	}
	else
	{

		waitpid(child_pid, &status, 0);
		set_last_exit_status(WIFEXITED(status) ? WEXITSTATUS(status) : 1);
		/*printf("The exit status is: %d\n", get_last_exit_status());*/
	}
}

/**
 * print_command_not_found - Print message indicating the command was not found
 * @command: The command that was not found
 * @program_name: The name of the program
 * @exit_status: The exit status to return
 * Return: void
*/
void print_command_not_found(char *command, char *program_name)
{
	fprintf(stderr, "%s: 1: %s: not found\n", program_name,  command);
}
