/* alias_command.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.c"

/**
 * struct Alias - Alias linked list node structure
 * @name: Name of the alias
 * @value: Value of the alias
 * @next: Pointer to next Alias node
*/
typedef struct Alias
{
	char *name;
	char *value;
	struct Alias *next;
} Alias;

static Alias *alias_list = NULL;

/**
 * alias_command - Handle the alias built-in command
 * @args: An array of strings containing the command and arguments.
 * @av: Argument vector.
 */
void alias_command(char **args, char **av)
{
    /* Skip the command name */
    (void)av;
    args++;

    if (*args == NULL)
    {
        /* Print all aliases */
        print_aliases();
    }
    else
    {
        /* Handle specific aliases */
        char **arg;

        for (arg = args; *arg != NULL; arg++)
        {
            /* Check if the argument has the form 'name=value' */
            char *equal_sign = strchr(*arg, '=');
            char *name;
            char *value;

            if (equal_sign != NULL)
            {
                /* Extract name and value */
                *equal_sign = '\0'; /* Replace '=' with null terminator */
                name = *arg;
                value = equal_sign + 1;

                /* Define alias */
                define_alias(name, value);
            }
            else
            {
                /* Print alias */
                print_alias(*arg);
            }
        }
    }
}

/**
 * print_aliases - Print all aliases
 */
void print_aliases(void)
{
    Alias *current = alias_list;

    while (current != NULL)
    {
        printf("%s='%s'\n", current->name, current->value);
        current = current->next;
    }
}

/**
 * print_alias - Print the value of a specific alias
 * @name: The name of the alias to print
 */
void print_alias(char *name)
{
    Alias *current = alias_list;
    int found = 0;

    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            printf("%s='%s'\n", current->name, current->value);
            found = 1;
            break;
        }
        current = current->next;
    }

    if (!found)
        printf("alias: %s: not found\n", name);
}

/**
 * define_alias - Define or update an alias
 * @name: The name of the alias
 * @value: The value of the alias
 */
void define_alias(char *name, char *value)
{
    /* Check if the alias already exists, and update its value if it does */
    Alias *current = alias_list;
    Alias *new_alias = malloc(sizeof(Alias));

    if (new_alias == NULL)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            free(current->value);
            current->value = strdup(value);
            free(new_alias); /* Free the newly allocated node */
            return;
        }
        current = current->next;
    }

    /* If the alias doesn't exist, create a new one and add it to the list */

    new_alias->name = strdup(name);
    new_alias->value = strdup(value);
    new_alias->next = alias_list;
    alias_list = new_alias;
}
