#ifndef SHELL_H
#define SHELL_H
int check_del(char a, char *del)
int check_alpha(int a)
int prompt(fun_t *func)
int _atoi(char *s)
int exit_shell(info_t *func)
int print_env(info_t *info)
char *get_env_value(info_t *info, const char *name)
int set_env_value(info_t *info, const char *name, const char *value)
int unset_env_value(info_t *info, const char *name)
int populate_env_list(info_t *info)

#endif
