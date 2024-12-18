#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

#define BUFFER_SIZE 1024
#define PROMPT "#cisfun$ "

extern char **environ;

/* Function prototypes */
void prompt(void);
void print_env(void);
char *read_command(void);
int execute_command(char *command);

#endif /* SHELL_H */
