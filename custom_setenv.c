#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * handle_setenv_command - Handle the setenv command.
 * @command: The command tokens.
 *
 *
 * Return: 0 on success, -1 on failure.
 */
void handle_setenv_command(char **command) {
    
    char *variable = command[1];
    char *value = command[2];
	/*char *updated_value;*/

	if (command[1] == NULL || command[2] == NULL) {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
        return;
    }

    

    
    if (setenv(variable, value, 1) == -1) {
        perror("setenv");
        return;
    }

    
    /*updated_value = getenv(variable);*/
    /* printf("%s=%s\n", variable, updated_value); */
}

/**
 * unsetenv_builtin - Unset environment variable
 * @command: Name of the environment variable to unset
 * Return: 0 on success, -1 on failure
 */

extern char **environ;

void unsetenv_builtin(char **command) {
    
	char **env_ptr = environ;

	if (command[1] == NULL || command[2] != NULL) {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        return;
    }

    /* Check if the variable exists before attempting to unset it */
    
    while (*env_ptr != NULL) {
        if (strncmp(*env_ptr, command[1], strlen(command[1])) == 0 &&
            (*env_ptr)[strlen(command[1])] == '=') {
            /* Variable found, unset it */
            if (unsetenv(command[1]) != 0) {
                fprintf(stderr, "Error: Unable to unset environment variable %s\n", command[1]);
            }
            return;
        }
        env_ptr++;
    }

    /* Variable not found */
    fprintf(stderr, "Error: Environment variable %s not found\n", command[1]);
}
