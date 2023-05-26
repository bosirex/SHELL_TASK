#ifndef _SHELL_H_
#define _SHELL_H_

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

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststring - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next nd
 */
typedef struct liststring
{
	int num;
	char *str;
	struct liststring *next;
} lst_t;

typedef struct passdat
{
	char *path;
	char *arg;
	char **argv;
	int argc;
	lst_t *env;
	lst_t *history;
	lst_t *alias;
	int line_count_flag;
	char *fname;
	char **environ;
	int env_changed;
	int status;
	unsigned int lenght_count;
	int err_number;
	
	

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int _readfd;
	int history_count;
} data_t;

#define dat_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - builtin string function
 * @type: builtin command flag
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(data_t *);
} table;


/* _string.c */
int string_len(char *);
int str_comparison(char *, char *);
char *_startswith(const char *, const char *);
char *string_cat(char *, char *);

/* _shell_loop.c */
int main_shell(data_t *, char **);
int builtin_find(data_t *);
void get_cmd(data_t *);
void _forkcmd(data_t *);

/* _loopmain_shell.c */
int loopmain_shell(char **);

/* _errors.c */
void _eputs(char *);
int _eputchar(char);
int fd_put(char c, int fd);
int putsfile_desc(char *str, int fd);

/* _string1.c */
char *string_cpy(char *, char *);
char *string_dup(const char *);
void _puts(char *);
int _putchar(char);

/* _parser.c */
int _iscmd(data_t *, char *);
char *dup_chars(char *, int, int);
char *_findpath(data_t *, char *, char *);

/* _exits.c */
char *str_copy(char *, char *, int);
char *string_concatenate(char *, char *, int);
char *string_character(char *, char);

/* _memory.c */
int ptr_free(void **);

/* _atoi.c */
int interactiv(data_t *);
int _isdelim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* _tokenizer.c */
char **string_word(char *, char *);
char **string_word2(char *, char);

/* _realloc.c */
char *mem_set(char *, char, unsigned int);
void f_free(char **);
void *real_loc(void *, unsigned int, unsigned int);

/* _errors1.c */
int _erratoi(char *);
void error_print(data_t *, char *);
int print_dec(int, int);
char *convt_number(long int, int, int);
void comments_remove(char *);

/* _builtin.c */
int _exits(data_t *);
int _cd(data_t *);
int _help(data_t *);

/* _builtin1.c */
int _history(data_t *);
int _alias(data_t *);

/* _getline.c */
ssize_t input_get(data_t *);
int get_line(data_t *, char **, size_t *);
void sigintHandler(int);

/* _getdat.c */
void clear_dat(data_t *);
void set_dat(data_t *, char **);
void free_dat(data_t *, int);

/* _lists.c */
lst_t *add_nd(lst_t **, const char *, int);
lst_t *add_nd_end(lst_t **, const char *, int);
size_t print_lst_str(const lst_t *);
int delete_nd_at_index(lst_t **, unsigned int);
void free_list(lst_t **);

/* _history.c */
char *get_hist_file(data_t *dat);
int wrt_history(data_t *dat);
int history_read(data_t *dat);
int build_history_list(data_t *dat, char *buf, int line_count);
int renumber_history(data_t *dat);


/* _lists1.c */
size_t length_list(const lst_t *);
char **lst_to_str(lst_t *);
size_t print_list(const lst_t *);
lst_t *nd_startswith(lst_t *, char *, char);
ssize_t get_nd_index(lst_t *, lst_t *);

/* _vars.c */
int _ischain(data_t *, char *, size_t *);
void check_chain(data_t *, char *, size_t *, size_t, size_t);
int replace_alias(data_t *);
int vars_replace(data_t *);
int _replacestring(char **, char *);

/* _environ.c */
char *get_env(data_t *, const char *);
int _env(data_t *);
int _setenviron(data_t *);
int _unsetenviron(data_t *);
int env_list_populate(data_t *);

/* _env.c */
char **get_environ(data_t *);
int _unsetenv(data_t *, char *);
int _setenv(data_t *, char *, char *);

#endif
