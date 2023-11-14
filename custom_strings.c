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
 * @n: Maximum number of characters to compare
 * Return: Integer value indicating whether
 *			s1 is less than, equal to, or greater than s2
*/

int custom_strcmp(const char *s1, const char *s2, size_t n)
{
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (n > 0 && *s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*s1 - *s2);
}

/**
 * custom_strdup - Duplicate a string.
 * @str: The string to be duplicated.
 *
 * Return: Pointer to the newly allocated memory containing a duplicate
 * of the string, or NULL if it fails.
 */
char *custom_strdup(const char *str)
{
	char *duplicate;
	unsigned int length = 0, i;

	if (str == NULL)
		return (NULL);

	while (str[length])
		length++;

	duplicate = (char *)malloc(sizeof(char) * (length + 1));

	if (duplicate == NULL)
		return (NULL);

	for (i = 0; i <= length; i++)
		duplicate[i] = str[i];

	duplicate[length] = '\0';

	return (duplicate);

}

/**
 * custom_strlen - Custom implementation of strlen function
 * @str: String to get length of
 *
 * Return: Length of string excluding terminating null byte
*/

size_t custom_strlen(const char *str)
{
	size_t length = 0;

	if (str == NULL)
	{
		return (0);
	}
	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}

