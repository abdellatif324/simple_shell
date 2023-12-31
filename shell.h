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


/* for read/write buffers */

#define READ_BUF_SIZE 1024

#define WRITE_BUF_SIZE 1024

#define BUF_FLUSH -1


/* for command chaining */

#define CMD_NORM        0

#define CMD_OR                1

#define CMD_AND                2

#define CMD_CHAIN        3


/* for convert_number() */

#define CONVERT_LOWERCASE        1

#define CONVERT_UNSIGNED        2


/* 1 if using system getline() */

#define USE_GETLINE 0

#define USE_STRTOK 0


#define HIST_FILE        ".simple_shell_history"

#define HIST_MAX        4096


extern char **environ;



/**

 * struct liststr - singly linked list

 * @num: the number field

 * @str: a string

 * @next: points to the next node

 */

typedef struct liststr

{

        int num;

        char *str;

        struct liststr *next;

} list_t;


/**

 * struct passinfo - contains pseudo-arguements to pass into a function,

 * allowing uniform prototype for function pointer struct

 * @arg: a string generated from getline containing arguements

 * @argv:an array of strings generated from arg

 * @path: a string path for the current command

 * @argc: the argument count

 * @line_count: the error count

 * @err_num: the error code for exit()s

 * @linecount_flag: if on count this line of input

 * @fname: the program filename

 * @env: linked list local copy of environ

 * @environ: custom modified copy of environ from LL env

 * @history: the history node

 * @alias: the alias node

 * @env_changed: on if environ was changed

 * @status: the return status of the last exec'd command

 * @cmd_buf: address of pointer to cmd_buf, on if chaining

 * @cmd_buf_type: CMD_type ||, &&, ;

 * @readfd: the fd from which to read line input

 * @histcount: the history line number count

 */

typedef struct passinfo

{

        char *arg;

        char **argv;

        char *path;

        int argc;

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


        char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */

        int cmd_buf_type; /* CMD_type ||, &&, ; */

        int readfd;

        int histcount;

} info_t;


#define INFO_INIT \
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

} builtin_table;

void _puts(char *str);


/**this part add*/
/*part ad again*/
#include <string.h>
void _puts(char *str);
int _setenv_var(info_t *info, const char *name, const char *value);
char *_getenv(info_t *info, const char *name);
int _setenv_var2(info_t *info, char *var, char *value);
int build_history_linked_list(info_t *info, char *buf, int linecount);
char **list_to_strings(list_t *list);
int some_max_length = 100;

int _myenv(info_t *info);
int _myhelp(info_t *info);

int _myhistory(info_t *info);
int _mysetenv(info_t *info);
int _mycd(info_t *info);
int _myalias(info_t *info);

int is_delim(char c, const char *delims);
char *find_path(info_t *info, const char *path_str, const char *command);
char *_strcpy2(char *dest, char *src);
void replace_vars(info_t *info);
void check_chain(info_t *info, char *buf, size_t *j, size_t i, size_t len);
list_t *node_starts_with(list_t *head, char *str, char delimiter);

/*char *_strcpy(char *dest, const char *src);
*/
/* toem_shloop.c */


int hsh(info_t *, char **);

int find_builtin(info_t *);

void find_cmd(info_t *);

void fork_cmd(info_t *);


/* toem_parser.c */

int _cmd(info_t *, char *);

char *_chars(char *, int, int);

char *_path(info_t *, char *, char *);


/* loophsh.c */

int loophsh(char **);


/* toem_errors.c */

void _eputs(char *);

int _eputchar(char);

int _put_character_fd(char c, int fd);

int _puts_string_fd(char *str, int fd);


/* toem_string.c */

int _strlen(char *);

int _strcmp(char *, char *);

char *starts_with(const char *, const char *);

char *_strcat(char *, char *);


/* toem_string1.c */

char *_strcpy(char *, char);
int _putchar(char);


/* toem_exits.c */

char *_strncpy(char *, char *, int);

char *_strncat(char *, char *, int);

char *_strlocach(char *, char);


/* toem_tokenizer.c */

char **strtow(char *, char *);

char **strtow2(char *, char);


/* toem_realloc.c */

char *_memset(char *, char, unsigned int);

void fffree(char **);

void *_realloc(void *, unsigned int, unsigned int);


/* toem_memory.c */

int beffur_free(void **);


/* toem_atoi.c */

int reactive(info_t *);

int checks_delim(char, char *);

int _isalpha(int);

int _atoi(char *);


/* toem_errors1.c */

int _erratoi(char *);

void print_error(info_t *, char *);

int print_decimal_integer(int, int);

char *convert_number(long int, int, int);

void remove_comment(char *);


/* toem_builtin.c */

int _exit_shell(info_t *);

int _changes_directory(info_t *);

int _changes_current_help(info_t *);


/* toem_builtin1.c */

int _show_historiq_list(info_t *);

int _mimics_alias(info_t *);


/*toem_getline.c */

ssize_t get_input(info_t *);

int _getline(info_t *, char **, size_t *);

void handlersigin_signal(int);


/* toem_getinfo.c */

void clear_info(info_t *);

void set_info(info_t *, char **);

void free_info(info_t *, int);


/* toem_environ.c */

char *_gets_value_variable(info_t *, const char *);

int _current_myenvironnment_alias(info_t *);

int _mysetenv(info_t *);

int _myremovenv(info_t *);

int populates_linked_list(info_t *);


/* toem_getenv.c */

char **get_environ(info_t *);

int _unsetenv_remo_remo(info_t *, char *);

int _setenv(info_t *, char *, char *);


/* toem_history.c */

char *get_history_file(info_t *info);

int write_history(info_t *info);

int read_history(info_t *info);

int build_history_list(info_t *info, char *buf, int linecount);

int renumber_history(info_t *info);


/* toem_lists.c */

list_t *add_node(list_t **, const char *, int);

list_t *add_node_end(list_t **, const char *, int);

size_t print_list(const list_t *);

int delete_node_at(list_t **, unsigned int);

void free_list(list_t **);


/* toem_lists1.c */

size_t list_len(const list_t *);

char **list_to(list_t *);

size_t print_lists(const list_t *);

list_t *node_starts(list_t *, char *, char);

ssize_t get_node_inde(list_t *, list_t *);


/* toem_vars.c */

int is_chain(info_t *, char *, size_t *);

void chain(info_t *, char *, size_t *, size_t, size_t);

int replace_alias(info_t *);

int vars(info_t *);

int replace_string(char **, char *);


#endif

