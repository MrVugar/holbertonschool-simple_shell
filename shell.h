#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handle_input(char *input);
void execute_command(char *command);

#endif /* SHELL_H */
