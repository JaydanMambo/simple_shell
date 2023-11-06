#include "prototypes.c"
/* custom string functions */

/**
 * custom_strcpy - Custom implementation of strcpy function
 * @dest: Destination string
 * @src: Source string
 * Return: Pointer to dest
*/

char *custom_strcpy(char *dest, const char *src)
{
	char *original_dest = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (original_dest);
}

/**
 * custom_strcat - Custom implementation of strcat function
 * @dest: Destination string
 * @src: Source string
 * Return: Pointer to dest
*/
char *custom_strcat(char *dest, const char *src)
{
	char *original_dest = dest;

	while (*dest != '\0')
	{
		dest++;
	}
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (original_dest);
}

/**
 * custom_strcmp - Custom implementation of strcmp function
 * @s1: String 1
 * @s2: String 2
 * Return: Integer value indicating whether
 *			s1 is less than, equal to, or greater than s2
*/
int custom_strcmp(const char *s1, const char *s2)
{
	if (s1 == NULL || s2 == NULL)
	{
		return (0);
	}
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	if (*s1 == '\0' && *s2 == '\0')
	{
		return (0);
	}
	else if (*s1 == '\0')
	{
		return (-1);
	}
	else
	{
		return (1);
	}
}
