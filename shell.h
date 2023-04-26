#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE  ".simple_shell_history"
#define HIST_MAX  4096

extern char **environ;

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
}list_t;


typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc:
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
}info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
}builtin_table;

int check_del(char c, char *del);
int check_alpha(int a);
int prompt(info_t *func);
int _atoi(char *s);
int exit_shell(info_t *func);

char **strtow(const char *str, const char *del);
char **str_split(char *str, char del);
int chain_del(info_t *func, char *buf, size_t *pos);
void check_chain(info_t *func, char *buf, size_t *pos, size_t i, size_t len);
void _realloc(void *ptr, unsigned int old, unsigned int neww);

int replace_alias(info_t *func);
int replace_string(char **old, char *neww);
int replace_vars(info_t *func);
char *memset(char *ptr, char a, unsigned int n);
void _free(char **str);p

int is_cmd(info_t *func, char *path);
char *dub_chars(char *path_str, int start, int end);
char *find_path(info_t *func, char *path_str, char *cmd);

int print_env(info_t *info);
char *get_env_value(info_t *info, const char *name);
int set_env_value(info_t *info, const char *name, const char *value);
int unset_env_value(info_t *info, const char *name);
int populate_env_list(info_t *info);

#endif
