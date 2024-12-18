#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

extern char **environ;

#define BUFFER_SIZE 1024
#define PROMPT "#cisfun$ "

void prompt(void)
{
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}

char *read_command(void)
{
    char *buffer = NULL;
    size_t len = 0;

    if (getline(&buffer, &len, stdin) == -1)
    {
        free(buffer);
        write(STDOUT_FILENO, "\n", 1);
        exit(EXIT_SUCCESS);
    }

    buffer[strcspn(buffer, "\n")] = '\0'; /* Remove newline */
    return buffer;
}

int execute_command(char *command)
{
    char *args[BUFFER_SIZE];
    char *token;
    pid_t pid;
    int status;

    token = strtok(command, " ");
    for (int i = 0; token != NULL; i++)
    {
        args[i] = token;
        token = strtok(NULL, " ");
    }
    args[BUFFER_SIZE - 1] = NULL;

    if (args[0] == NULL)
        return 1;

    if (strcmp(args[0], "exit") == 0)
        exit(EXIT_SUCCESS);

    if (strcmp(args[0], "env") == 0)
    {
        for (int i = 0; environ[i] != NULL; i++)
            printf("%s\n", environ[i]);
        return 1;
    }

    pid = fork();
    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("Error");
    }
    else
    {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int main(void)
{
    char *command;

    while (1)
    {
        prompt();
        command = read_command();
        execute_command(command);
        free(command);
    }

    return 0;
}

