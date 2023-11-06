#include <unistd.h>
#include <stdlib.h>
#include "prototypes.c"

#define READ_SIZE 1024

/**
 * custom_getline - Read a line from a file descriptor
 * @lineptr: A pointer where the line will be stored
 * @n: A pointer to the size of the buffer
 * @fd: The file descriptor from which to read input
 *
 * Return: The number of characters read or -1 on error
 */
ssize_t custom_getline(char **lineptr, size_t *n, int fd)
{
	size_t bufsize = READ_SIZE;
	ssize_t pos = 0;
	char *buffer = NULL;
	char ch;

	if (!lineptr || !n || bufsize < 1)
		return (-1);
	buffer = malloc(bufsize);
	if (!buffer)
		return (-1);
	while (1)
	{
		if (read(fd, &ch, 1) <= 0)
			break;
		if ((size_t)pos >= bufsize - 1)
		{
			bufsize *= 2;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
				return (-1);
		}
		buffer[pos++] = ch;
		if (ch == '\n')
			break;
	}
	if (pos == 0)
	{
		free(buffer);
		return (-1);
	}
	buffer[pos] = '\0';
	*lineptr = buffer;
	*n = bufsize;
	if (ch == EOF)
	{
		free(buffer);
		return (-1);
	}
	return (pos);

}
