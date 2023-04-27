#include "shell.h"

/**
 * check_del - function checks delimeter character
 * @a: character to check
 * @del: the delimeter string
 * Return: 1 on success
 */

int check_del(char a, char *del)
{
	while (*del != '\0')
		if (*del == a)
			return (1);
	return (0);
}

/**
 * check_alpha - function that checks for alphabets
 * @a: character to check
 * Return: 1 on success
 */

int check_alpha(int a)
{
	if ((a >= 97 && a <= 122) || (a >= 65 && a <= 90))
		return (1);
	else
		return (0);
}

/**
 * prompt - function that checks if shell is interactive
 * @func: struct address
 * Return: 1 on success
 */

int prompt(info_t *func)
{
	if (isatty(STDIN_FILENO) && func->readfd <= 2)
		return (1);
	else
		return (0);
}



/**
 * _atoi - function that converts strings to integer
 * @s: string to convert
 * Return: converted number
 */

int _atoi(char *s)
{
	int i, sign = 1;
	int output, flag = 0;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}



/**
 * exit_shell - function that exit shell\
 * @func: struct for arguments
 * Return: exit on success
 */

int exit_shell(info_t *func)
{
	if (func->argv[1])
	{
		char *endptr;
		int exitval = strtol(func->argv[1], &endptr, 10);

		if (*endptr != '\0')
		{
			func->status = 2;
			print_error(func, "illegal number; ");
			_eputs(func->argv[1]);
			_eputchar('\n');
			return (1);
		}
		func->err_num = exitval;
	}
	else
		func->err_num = -1;
	return (-2);
}


