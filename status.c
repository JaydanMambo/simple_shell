#include "prototypes.c"

static int last_exit_status;
static pid_t last_process_id;
static int last_child_exit_status;

/**
 * get_last_exit_status - Get the last exit status
 *
 * Return: The last exit status
 */
int get_last_exit_status(void)
{
	return (last_exit_status);
}

/**
 * get_child_exit_status - Get the last exit status
 *
 * Return: The last exit status
 */
int get_child_exit_status(void)
{
	return (last_child_exit_status);
}

/**
 * get_last_process_id - Get the last process ID
 *
 * Return: The last process ID
 */
pid_t get_last_process_id(void)
{
	return (last_process_id);
}

/**
 * set_last_exit_status - Set the last exit status
 * @status: The exit status to set
 */
void set_last_exit_status(int status)
{
	last_exit_status = status;
}

/**
 * set_child_exit_status - Set the last exit status
 * @status: The exit status to set
 */
void set_child_exit_status(int status)
{
	last_child_exit_status = status;
}

/**
 * set_last_process_id - Set the last process ID
 * @pid: The process ID to set
 */
void set_last_process_id(pid_t pid)
{
	last_process_id = pid;
}
