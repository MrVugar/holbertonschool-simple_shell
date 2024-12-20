#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64
#define MAX_PATH_LENGTH 2048

extern char **environ; // Declare environ

char *search_path(char *command);

int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];
    pid_t pid;
    int status, arg_count;
    char *token;
    char *command_path;
    char *prompt = ":) ";

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("%s", prompt);
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            if (isatty(STDIN_FILENO))
                printf("\n");
            break;
        }
        command[strcspn(command, "\n")] = '\0';

        // Tokenize command line
        arg_count = 0;
        token = strtok(command, " ");
        while (token != NULL && arg_count < MAX_ARGS - 1)
        {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;

        if (args[0] == NULL)
            continue;

        // Search path
        command_path = search_path(args[0]);

        if (command_path == NULL)
        {
            fprintf(stderr, "%s: No such file or directory\n", args[0]);
            continue;
        }

        pid = fork();

        if (pid == -1)
        {
            perror("fork");
            free(command_path);
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Child process
            if (execve(command_path, args, environ) == -1)
            {
                perror("./shell");
                free(command_path);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            // Parent process
            if (waitpid(pid, &status, 0) == -1)
            {
                perror("waitpid");
                free(command_path);
                exit(EXIT_FAILURE);
            }
            free(command_path);
        }
    }
    return (EXIT_SUCCESS);
}

char *search_path(char *command)
{
    char *path = getenv("PATH");
    char *path_copy, *dir, *file_path;
    struct stat buffer;

    if (path == NULL || command == NULL)
    {
        return NULL;
    }

    if (strchr(command, '/') != NULL)
    {
        if (stat(command, &buffer) == 0)
            return strdup(command);
        return NULL;
    }

    path_copy = strdup(path);
    if (path_copy == NULL)
    {
        perror("strdup");
        return NULL;
    }

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        file_path = malloc(strlen(dir) + strlen(command) + 2);
        if (file_path == NULL)
        {
            perror("malloc");
            free(path_copy);
            return NULL;
        }
        sprintf(file_path, "%s/%s", dir, command);
        if (stat(file_path, &buffer) == 0)
        {
            free(path_copy);
            return file_path;
        }

        free(file_path);
        dir = strtok(NULL, ":");
    }
    free(path_copy);
    return NULL;
}
