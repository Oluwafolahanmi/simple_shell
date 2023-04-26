#include "shell.h"

/**
 * strtow - function that splits strings into words
 * @str: input string
 * @del: delimeter strings
 * Return: pointer to an array or NULL on failure
 */

char **strtow(const char *str, const char *del)
{
	int len, j, i, k, numwords = 0;
	char **words;

	if (str == NULL || *str == '\0')
		return (NULL);
	if (del == NULL)
		del = DEFAULT_DELIM;
	for (i = 0, str[i] != '\0', i++)
		if (!check_del(str[i], del) && (check_del(str[i + 1], del) || !str[i + 1]))
			numwords++;
	if (numwords == 0)
		return (NULL);
	words = malloc(numwords + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (check_del(str[i], del))
			i++;
		k = 0;
		while (!check_del(str[i + k], del) && stri + k)
			k++;
		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}
		for (len = 0; len < k; len++)
			words[j][len] = str[i++];
		words[j][len] = 0;
	}
	words[j] = NULL;
	return (words);
}



/**
 * str_split - function splits stringd into substrings
 * @str: string to split
 * @del: delimeters
 * Return: pointer to an array of strings
 */

char **str_split(char *str, char del)
{
	int i, j, k, len, numwords = 0;
	char **words;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != del && str[i + 1] == del) ||
					(str[i] != del && str[i + 1] == del || str[i + 1] == '\0'))
			numwords++;
	if (numwords == '\0')
		return (NULL);
	words = malloc((1 + numwords) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == del && str[i] != '\0')
			i++;
		k = 0;
		while (str[i + k] != del && str[i + k] != '\0')
			k++;
		words[j] = malloc((k + 1) * sizeof(char));
		if (words[j] == NULL)
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}
		for (len = 0; len < k; len++)
			words[j][len] = str[i++];
		words[j][len] = 0;
	}
	words[j] = NULL;
	return (words);
}

/**
 * chain_del - function that checks for chain dlimeter
 * @func: struck parameter
 * @buf: char buffer
 * @pos: current position address
 * Return: 1 on success
 */

int chain_del(info_t *func, char *buf, size_t *pos)
{
	size_t a = *pos;

	if (buf[a] == '|' && buf[a + 1] == '|')
	{
		buf[a] = 0;
		a++;
		funcc->cmd_buf_type = CMD_OR;
	}
	else if (buf[a] == '&' && buf[a + 1] == '&')
	{
		buf[a] = 0;
		a++;
		func->cmd_buf_type = CMD_AND;
	}
	else if (buf[a] == ';')
	{
		buf[a] = 0;
		func->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = a;
	return (1);
}



/**
 * check_chain - checks last status chaining
 * @func: struct parameter
 * @buf: char buffer
 * @pos: buffer current position
 * @i: starting position in buffer
 * @len: length of buffer
 */

void check_chain(info_t *func, char *buf, size_t *pos, size_t i, size_t len)
{
	size_t a = *pos;

	if (func->cmd_buf_type == CMD_AND)
	{
		if (func->status)
		{
			buf[i] = 0;
			a = len;
		}
	}
	if (func->cmd_buf_type == CMD_OR)
	{
		if (!func->status)
		{
			buf[i] = 0;
			a = len;
		}
	}
	*pos = a;
}


/**
 * _realloc - reallocate memory block
 * @ptr: pointer to previous block
 * @old: size of old block
 * @new: size of new block
 * Return: pointer to old block
 */

void *_realloc(void *ptr, unsigned int old, unsigned int new)
{
	char *b;

	if (ptr == NULL)
		return (malloc(new));
	if (new == NULL)
		return (free(ptr), NULL);
	if (new == old)
		return (ptr);

	b = malloc(new);
	if (b == NULL)
		return (NULL);

	old = old < new ? old : new;
	while (old--)
		b[old] = ((char *)ptr)[old];
	free(ptr);
	return (b);
}
