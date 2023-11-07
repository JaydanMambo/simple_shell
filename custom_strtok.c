#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "prototypes.c"

/**
 * skip_delimiters - Skip delimiter characters in a string
 * @str: The string to skip delimiters in
 * @delim: The delimiter characters
 *
 * Return: A pointer to the next non-delimiter character or NULL if at the end
 */
static char *skip_delimiters(char *str, const char *delim)
{
	char *delim_ptr;

	while (*str)
	{
		bool found = false;

		delim_ptr = (char *)delim;
		while (*delim_ptr)
		{
			if (*str == *delim_ptr)
			{
				found = true;
				break;
			}
		delim_ptr++;
		}

		if (!found)
		{
			break;
		}
		str++;
	}

	return ((*str == '\0') ? NULL : str);
}

/**
 * custom_strtok - Custom string tokenizer
 * @str: The string to tokenize
 * @delim: The delimiter characters
 *
 * Return: A pointer to the next token or NULL if there are no more tokens
 */
char *custom_strtok(char *str, const char *delim)
{
	static char *last_token;
	char *token, *str_ptr;

	if (str != NULL)
		last_token = str;
	else if (last_token == NULL)
		return (NULL);
	last_token = skip_delimiters(last_token, delim);
	if (last_token == NULL)
		return (NULL);
	token = last_token;
	str_ptr = last_token + 1;
	while (*str_ptr)
	{
		bool found = false;
		char *delim_ptr = (char *)delim;

		while (*delim_ptr)
		{
			if (*str_ptr == *delim_ptr)
			{
				found = true;
				break;
			}
			delim_ptr++;
		}
		if (found)
		{
			break;
		}
		str_ptr++;
	}
	if (*str_ptr != '\0')
	{
		*str_ptr = '\0';
		last_token = str_ptr + 1;
	}
	else
		last_token = NULL;
return (token);
}
