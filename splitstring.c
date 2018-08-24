#include "holberton.h"
/**
 * splitstring - tokenize a string and puts tokens into array
 * @buffer: buffer to hold the command
 *
 * Return: array of string tokens
 */

char **splitstring(char *buffer)
{
	char **array = NULL;
	char *token;
	int count = 0;
	int elements_c = 0;
	char *tmpbuffer = 0;

	/* Check if buffer is not NULL */
	if (buffer == NULL)
		return (NULL);

	/* Remove the new line from buffer */
	buffer = strtok(buffer, "\n");

	/* make a copy of the buffer */
	tmpbuffer = strdup(buffer);

	/* Calculate the number of arguments */
	strtok(tmpbuffer, " ");
	while (strtok(NULL, " "))
		elements_c++;

	/* Allocate memory for the array */
	array = malloc(sizeof(char *) * (elements_c + 1));

	/* Populate the array */
	token = strtok(buffer, " ");
	count = 0;
	array[count] = token;
	for (count = 1; count < elements_c + 1; count++)
	{
		token = strtok(NULL, " ");
		array[count] = token;
	}
	array[count] = NULL;

	return (array);
}
