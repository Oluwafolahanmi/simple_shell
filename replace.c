#include "shell.h"

/**
 * replace_alias -  replace alias in tokenized strings
 * @func: struct parameter
 * Return: 1 if replaced
 */

int replace_alias(info_t *func)
{
	int i;
	char *pos;
	list_t *node;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(func->alias, func->argv[0], '=');
		if (node == NULL)
			return (0);
		free(func->argv[0]);
		pos = _strchr(node->str, '=');
		if (pos == NULL)
			return (0);
		pos = _strdup(pos + 1);
		if (pos == NULL)
			return (0);
		func->argv[0] = pos;
	}
	return (1);
}

/**
 * replace_string - function replaces string
 * @old: old string address
 * @neww: new string
 * Return: 1 if replaced
 */

int replace_string(char **old, char *neww)
{
	free(*old);
	*old = neww;
	return (1);
}


/**
 * replace_vars - replaces vars in tokenised string
 * @func: structure parameter
 * Return: 1 if replaced
 */

int replace_vars(info_t *func)
{
	int i;
	list_t *node;
	char *num_str, *pid_str;

	for (i = 0; func->argv[i]; i++)
	{
		if (func->argv[i][0] != '$' || func->argv[i][1] == '\0')
			continue;

		if (!_strcmp(func->argv[i], "$?"))
		{
			num_str = convert_number(func->status, 10, 0)
			replace_string(&(func->argv[i]), _strdup(num_str));
			free(num_str);
			continue;
		}
		if (!_strcmp(func->argv[i], "$$"))
		{
			pid_str = convert_number(getpid(), 10, 0);
			replace_string(&(func->argv[i]), _strdup(pid_str));
			free(pid_str);
			continue;
		}
		node = node_starts_with(func->env, &func->argv[i][1], '=');
		if (node)
		{
			replace_string(&(func->argv[i]), _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&(func->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * memset - function fills memory with constant byte
 * @ptr: pointer to the memory area
 * @a: byte to set
 * @n: number of bytes to set
 * Return: pointer to memory area
 */

char *memset(char *ptr, char a, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		ptr[i] = a;
	return (ptr);
}


/**
 * _free - frees array of strings
 * @str: array of strings
 */

void _free(char **str)
{
	char **k = str;

	if (str == NULL)
		return;
	while (*str)
		free(*str++);
	free(k);
}
