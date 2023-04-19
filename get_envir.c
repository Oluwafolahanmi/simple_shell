#include "shell.h"

/**
 * print_env - Prints the current environment variables and their values
 * @info: Structure containing the environment variables list
 *
 * Return: Always 0
 */
int print_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * get_env_value - Gets the value of an environment variable
 * @info: Structure containing the environment variables list
 * @name: The name of the environment variable to get
 *
 * Return: The value of the environment variable or NULL if not found
 */
char *get_env_value(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_env_value - Sets the value of an existing environment variable or
 *                 creates a new environment variable if it does not exist
 * @info: Structure containing the environment variables list
 * @name: The name of the environment variable to set
 * @value: The value to set the environment variable to
 *
 * Return: 0 on success, -1 on failure
 */
int set_env_value(info_t *info, const char *name, const char *value)
{
	char *env_var;
	size_t name_len = strlen(name), value_len = strlen(value);
	int result;

	env_var = malloc(name_len + value_len + 2);
	if (env_var == NULL)
		return (-1);

	result = snprintf(env_var, name_len + value_len + 2, "%s=%s", name, value);
	if (result < 0 || (size_t) result != name_len + value_len + 1)
	{
		free(env_var);
		return (-1);
	}

	if (_setenv(info, name, env_var) != 0)
	{
		free(env_var);
		return (-1);
	}

	free(env_var);
	return (0);
}

/**
 * unset_env_value - Unsets an environment variable
 * @info: Structure containing the environment variables list
 * @name: The name of the environment variable to unset
 *
 * Return: 0 on success, -1 on failure
 */
int unset_env_value(info_t *info, const char *name)
{
	return (_unsetenv(info, name));
}

/**
 * populate_env_list - Populates the environment variables list
 * @info: Structure containing the environment variables list
 *
 * Return: 0 on success, -1 on failure
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
	{
		if (add_node_end(&node, environ[i], 0) == NULL)
			return (-1);
	}

	info->env = node;
	return (0);
}
