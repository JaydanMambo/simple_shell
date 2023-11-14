#include <stdlib.h>
#include <stdio.h>



/**
 * shell_exit - Exit the shell with status
 * @exit_status: The exit status to return to the OS
*/
void shell_exit(int exit_status)
{
	exit(exit_status);
}

/**
 * handle_exit_command - Handle the exit built-in command
 * @command: The command and its arguments
 */
void handle_exit_command(char **command)
{
	int status = 0;

	if (command[1] != NULL)
	{
		/* Convert the status argument to an integer */
		status = atoi(command[1]);
		if (status == 0 && command[1][0] != '0')
		{
			/* Invalid status argument, set status to 2 */
			status = 2;
		}
	}

	/* Free the command array before exiting */
	free(command);

	/* Exit the shell with the specified status */
	exit(status);
}
