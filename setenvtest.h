#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * copy_info - Concatenates name and value to create a new environment variable.
 * @name: Name of the environment variable.
 * @value: Value of the environment variable.
 *
 * Returns: New environment variable string.
 */
char *copy_info(const char *name, const char *value) {
    size_t len = strlen(name) + strlen(value) + 2; // +2 for '=' and null terminator
    char *new = malloc(len);
    if (!new) {
        perror("Memory allocation failure");
        exit(EXIT_FAILURE);
    }

    snprintf(new, len, "%s=%s", name, value);
    return new;
}

/**
 * set_env - Sets or updates an environment variable.
 * @name: Name of the environment variable.
 * @value: Value to set for the environment variable.
 * @environ: Array of environment variables.
 *
 * Returns: 0 on success, -1 on failure.
 */
int set_env(const char *name, const char *value, char ***environ) {
    int i;
    char *var_env, *name_env;

    for (i = 0; (*environ)[i]; i++) {
        var_env = strdup((*environ)[i]);
        if (!var_env) {
            perror("Memory allocation failure");
            exit(EXIT_FAILURE);
        }

        name_env = strtok(var_env, "=");
        if (strcmp(name_env, name) == 0) {
            free((*environ)[i]);
            (*environ)[i] = copy_info(name_env, value);
            free(var_env);
            return 0; // Success
        }

        free(var_env);
    }

    // Variable doesn't exist, add a new one
    *environ = realloc(*environ, (i + 2) * sizeof(char *));
    if (!*environ) {
        perror("Memory allocation failure");
        exit(EXIT_FAILURE);
    }

    (*environ)[i] = copy_info(name, value);
    (*environ)[i + 1] = NULL;
    return 0; // Success
}

/**
 * custom_setenv - Wrapper for set_env to handle command arguments.
 * @command: Command tokens (arguments).
 * @environ: Array of environment variables.
 *
 * Returns: 0 on success, -1 on failure.
 */
int custom_setenv(char **command, char ***environ) {
    if (!command[1] || !command[2] || command[3]) {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
        return -1; // Invalid usage
    }

    return set_env(command[1], command[2], environ);
}

/**
 * custom_unsetenv - Removes an environment variable.
 * @command: Command tokens (arguments).
 * @environ: Array of environment variables.
 *
 * Returns: 0 on success, -1 on failure.
 */
int custom_unsetenv(char **command, char ***environ) {
    if (!command[1] || command[2]) {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        return -1; // Invalid usage
    }

    char **realloc_environ;
    char *var_env, *name_env;
    int i, j, k;

    for (i = 0; (*environ)[i]; i++) {
        var_env = strdup((*environ)[i]);
        if (!var_env) {
            perror("Memory allocation failure");
            exit(EXIT_FAILURE);
        }

        name_env = strtok(var_env, "=");
        if (strcmp(name_env, command[1]) == 0) {
            k = i; // Variable found
        }

        free(var_env);
    }

    if (!k) {
        fprintf(stderr, "Variable not found: %s\n", command[1]);
        return -1; // Variable not found
    }

    realloc_environ = malloc(i * sizeof(char *));
    if (!realloc_environ) {
        perror("Memory allocation failure");
        exit(EXIT_FAILURE);
    }

    for (i = j = 0; (*environ)[i]; i++) {
        if (i != k) {
            realloc_environ[j++] = (*environ)[i];
        }
    }

    realloc_environ[j] = NULL;
    free((*environ)[k]);
    free(*environ);
    *environ = realloc_environ;
    return 0; // Success
}
