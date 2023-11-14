#include <stdlib.h>
#include <string.h>
#include "prototypes.c"

/**
 * custom_getenv - Get the value of an environment variable
 * @name: The name of the environment variable
 *
 * Return: The value of the environment variable or NULL if not found
 */
char *custom_getenv(const char *name)
{
	extern char **environ;

	char **env;

	for (env = environ; *env != NULL; env++)
	{
		char *var = *env;

		if (custom_strcmp(var, name, custom_strlen(name)) == 0)
		{
			char *value = custom_strchr(var, '=') + 1;

			return (value);
		}
	}
	return (NULL);
}

/**
 * custom_strchr - Locate the first occurrence of a character in a string
 * @s: The string to search in
 * @c: The character to search for
 * Return: A pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */
char *custom_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			return ((char *)s); /* Cast to char* to match the original strchr function*/
		}
		s++;
	}

	if (c == '\0')
	{
		return ((char *)s); /*Return a pointer to the null terminator if c is '\0'*/
	}

	return (NULL);
}
