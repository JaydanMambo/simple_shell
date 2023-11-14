#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * _setenv - Changes or adds an environment variable.
 * @name: Name of the environment variable.
 * @value: Value to set for the environment variable.
 * @overwrite: Flag indicating whether to overwrite ifvariable already exists.
 *
 * Return: 0 on success, -1 on failure.
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	size_t len;
	char *env_var;
	char *existing_value;

	if (!name || name[0] == '\0' || strchr(name, '=') || !value)
		return (-1); /* Invalid input */

	/* Check if the variable already exists */
	existing_value = getenv(name);

	if (existing_value)
	{
		if (!overwrite)
			return (0); /* Variable exists, and overwrite is not allowed */
	}

	/* Concatenate name and value to form the assignment string */
	len = strlen(name) + strlen(value) + 2; /*+2 for '=' and null terminator*/
	env_var = malloc(len);
	if (!env_var)
		return (-1); /* Memory allocation failure */

	snprintf(env_var, len, "%s=%s", name, value);

	/* Putenv the new environment variable */
	if (putenv(env_var) != 0)
	{
		free(env_var);
		return (-1); /* Error setting environment variable */
	}

	return (0); /* Success */
}

/**
 * custom_setenv - Set or update an environment variable.
 * @name: Name of the environment variable.
 * @value: Value to set for the environment variable.
 * @environ: The environment variables.
 *
 * Return: 0 on success, -1 on failure.
 */
int custom_setenv(const char *name, const char *value)
{
	int overwrite = 1; /* Allow overwriting existing variable */

	if (_setenv(name, value, overwrite) != 0)
	{
		perror("Error setting environment variable");
		return (-1);
	}

	return (0);
}

/**
 * handle_setenv_command - Handle the setenv command.
 * @command: The command tokens.
 * @environ: The environment variables.
 *
 * Return: 0 on success, -1 on failure.
 */
int handle_setenv_command(char **command)
{
	if (command[1] == NULL || command[2] == NULL || command[3] != NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (-1);
	}

	return (custom_setenv(command[1], command[2]));
}
