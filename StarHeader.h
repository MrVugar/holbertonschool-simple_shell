#ifndef STARHEADER_H
#define STARHEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <linux/limits.h>

#define BUFFER_SIZE 1024

/* Function prototypes */
int execute_command(char **args, char **environ, char *program_name);
char **split_string(char *str);
char *_strdup(const char *str);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_getenv(const char *name, char **environ);
char *find_in_path(char *command, char **environ);
char *get_command_path(char *command, char **environ);
void print_env(char **environ);
int handle_builtin_commands(char **args, char *input,
	char **environ, char *program_name);
void remove_newline(char *str);
void display_prompt(void);
void execute_child_process(char *command_path, char **args, char **environ);
int execute_ls_with_color(char **args, char **environ);
int builtin_cd(char **args, char **env);
void sigint_handler(int sig);
int shell_exit(char **args, char *input, char *program_name);
int _atoi(char *s);
int help_builtin(char **args);
int is_valid_number(const char *str);
void help_builtin_cmd(char **args);

#endif /* STARHEADER_H */
