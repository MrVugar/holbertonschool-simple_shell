#include "StarHeader.h"

/**
 * _atoi - from a char string, extract numbers, and convert into int
 * @s: string to be tested
 *
 * Return: 0 if success
 */
int _atoi(char *s)
{
	int a, sign, numb;

	/* Initialize variables */
	a = 0, sign = 1, numb = 0;

	/* Iterate through each character of the string */
	while (s[a] != '\0')
	{
		/* Check for negative sign */
		if (s[a] == '-')
			sign *= -1;

		/* Check if character is a digit */
		if (s[a] >= '0' && s[a] <= '9')
		{
			/* Convert consecutive digits to integer */
			while (s[a] >= '0' && s[a] <= '9')
			{
				numb = (s[a] - '0') * sign + numb * 10;
				a++;
			}
			/* Exit loop after processing digits */
			break;
		}
		a++;
	}
	/* Return the extracted number */
	return (numb);
}

/**
 * is_valid_number - checks if exit code is a valid number.
 * @str: string to be tested
 * Return: 1 if valid
 *          0 if not valid
 */
int is_valid_number(const char *str)
{
	int i = 0;

	/* Check if the first character is a plus sign */
	if (str[0] == '+')
		i++;

	/* Iterate through each character */
	for (; str[i] != '\0'; i++)
	{
		/* Check if character is not a digit */
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}

	/* If all characters are digits, return 1 (valid) */
	return (1);
}
