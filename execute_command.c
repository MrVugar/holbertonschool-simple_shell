#include "shell.h"

void execute_command(char *command)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    if (pid == 0)
    {
        if (execvp(command, NULL) == -1)
        {
            perror("execvp");
            exit(1);
        }
    }
    else
    {
        wait(NULL);
    }
}
