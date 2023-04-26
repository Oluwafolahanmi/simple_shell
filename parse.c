#include "shell.h"

/**
 * is_cmd - detremines if file is executable
 * @func: struct
 * @path: path to the file
 * Return: 1 on success
 */

int is_cmd(info_t *func, char *path)
{
	struct stat st;

	(void)func;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicate characters
 * @path_str: the path string
 * @start: starting index
 * @end: stopping index
 * Return: pointer to new buffer
 */

char *dup_chars(char *path_str, int start, int end)
{
	static char buf[1024];
	int i, j = 0;

	for (j = 0, i = start; i < end; i++)
		if (path_str[i] != ':')
			buf[j++] = path_str[i];
	buf[j] = '\0';
	return (buf);
}


/**
 * find_path - finds cmd in path string
 * @func: structure
 * @path_str: path string
 * @cmd: the cmd to find
 * Return: full path of cmd
 */

char find_path(info_t *func, char *path_str, char *cmd)
{
	int i, current;
	char *path;

	i = 0;
	current = 0;
	if (path_str == NULL)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(func, cmd))
			return (cmd);
	}
	while (1)
	{
		if (path_str[i] == '\0' || path_str[i] == ':')
		{
			path = dup_chars(path_str, current, (i - current));
			if (*path == '\0')
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(func, path))
				return (path);
			if (path_str[i] == '\0')
				break;
			current = i + 1;
		}
		i++;
	}
	free(path);
	return (NULL);
}
