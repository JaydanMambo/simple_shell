#ifndef PROTOTYPES_C
#define PROTOTYPES_C

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

#define IS_EXIT_COMMAND(command) (command != NULL && \
	custom_strcmp(command[0], "exit", custom_strlen("exit")) == 0)
#define IS_ENV_COMMAND(command, env) (command != NULL && \
	custom_strcmp(command[0], "env", custom_strlen("env")) == 0)
#define IS_SETENV_COMMAND(command) (command != NULL && \
	custom_strcmp(command[0], "setenv", custom_strlen("setenv")) == 0)
/* #define HAS_AND_OPERATOR(input) (contains_logical_operator((const char **)input, "&&")) */


/* Custom string functions */
char *custom_strcpy(char *dest, const char *src);
char *custom_strcat(char *dest, const char *src);
int custom_strcmp(const char *s1, const char *s2, size_t n);
char *custom_strdup(const char *str);
size_t custom_strlen(const char *str);
char *custom_strchr(const char *s, int c);

/* Other function prototypes */
char **parse_input(char *input);
void trim_input(char *str);
void execute_command(char **command, char **av);
ssize_t custom_getline(char **lineptr, size_t *n, int fd);
void execute_in_current_directory(char **command, char **av);
void search_and_execute(char **command, char **av);
void execute_in_directory(char *command_path, char **command, char **av);
void print_command_not_found(char *command, char *program_name);
char *custom_getenv(const char *name);
void shell_exit(int exit_status);
void handle_exit_command(char **command);
void custom_env(int ac, char **av, char **env);
int custom_setenv(const char *name, const char *value);
int handle_setenv_command(char **command);
void execute_command_with_and(char *input, char **av);

bool contains_logical_operator(const char *input, const char *operator);
char **parse_commands_separated_by_semicolon(char *input);
char **parse_input_with_and(char *input);

void cd_command(char **command, char **av);
char *custom_getcwd(char *buffer, size_t size);
int get_last_exit_status(void);
pid_t get_last_process_id(void);
void set_last_process_id(pid_t pid);
void set_last_exit_status(int status);
int get_child_exit_status(void);
void set_child_exit_status(int status);




/* Custom string tokenizer */
char *custom_strtok(char *str, const char *delim);

/* Alias functions*/
void alias_command(char **args, char **av);
void print_aliases(void);
void print_alias(char *name);
void define_alias(char *name, char *value);

#endif /* PROTOTYPES_C */
