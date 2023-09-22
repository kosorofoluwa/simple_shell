#include "shell.h"

/**
 * printf - prints strings
 * @str: strings to be iterated and prrinted to the screen
 *
 * Return: returns iterator
 */
int _printf(char *str)
{
	int i = 0, itr = 0;
	while (str[i])
        {
		itr += _putchar(str[i++]);
	}
	return (itr);
}
