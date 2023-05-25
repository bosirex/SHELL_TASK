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


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next nd
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} lst_t;

typedef struct passdat
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int ln_count;
	int err_num;
	int line_count_flag;
	char *fname;
	lst_t *env;
	lst_t *history;
	lst_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define dat_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} table;


/* shell_loop.c */
int main_shell(info_t *, char **);
int builtin_find(info_t *);
void get_cmd(info_t *);
void _forkcmd(info_t *);

/* parser.c */
int _iscmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *_findpath(info_t *, char *, char *);

/* loopmain_shell.c */
int loopmain_shell(char **);

/* errors.c */
void _eputs(char *);
int _eputchar(char);
int put_fd(char c, int fd);
int putsfile_desc(char *str, int fd);

/* string.c */
int string_len(char *);
int _strcmp(char *, char *);
char *_startswith(const char *, const char *);
char *string_cat(char *, char *);

/* string1.c */
char *string_copy(char *, char *);
char *string_dup(const char *);
void _puts(char *);
int _putchar(char);

/* exits.c */
char *string_copy(char *, char *, int);
char *string_concatenate(char *, char *, int);
char *string_character(char *, char);

/* tokenizer.c */
char **string_word(char *, char *);
char **string_word2(char *, char);

/* real_loc.c */
char *mem_set(char *, char, unsigned int);
void f_free(char **);
void *real_loc(void *, unsigned int, unsigned int);

/* memory.c */
int ptr_free(void **);

/* atoi.c */
int interactiv(info_t *);
int _isdelim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* errors1.c */
int _erratoi(char *);
void error_print(info_t *, char *);
int print_dec(int, int);
char *convt_number(long int, int, int);
void comments_remove(char *);

/* builtin.c */
int _exit(info_t *);
int _cd(info_t *);
int _help(info_t *);

/* builtin1.c */
int _history(info_t *);
int _alias(info_t *);

/*getline.c */
ssize_t input_get(info_t *);
int get_line(info_t *, char **, size_t *);
void sigintHandler(int);

/* getdat.c */
void clear_dat(info_t *);
void set_dat(info_t *, char **);
void free_dat(info_t *, int);

/* environ.c */
char *get_env(info_t *, const char *);
int _env(info_t *);
int _setenv(info_t *);
int _unsetenv(info_t *);
int env_list_populate(info_t *);

/* env.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* history.c */
char *get_hist_file(info_t *dat);
int wrt_history(info_t *dat);
int history_read(info_t *dat);
int build_history_list(info_t *dat, char *buf, int line_count);
int renumber_history(info_t *dat);

/* lists.c */
lst_t *add_nd(lst_t **, const char *, int);
lst_t *add_nd_end(lst_t **, const char *, int);
size_t print_lst_str(const lst_t *);
int delete_nd_at_index(lst_t **, unsigned int);
void free_list(lst_t **);

/* lists1.c */
size_t length_list(const lst_t *);
char **lst_to_str(lst_t *);
size_t print_list(const lst_t *);
lst_t *nd_startswith(lst_t *, char *, char);
ssize_t get_nd_index(lst_t *, lst_t *);

/* vars.c */
int _ischain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int vars_replace(info_t *);
int _replacestring(char **, char *);

#endif
