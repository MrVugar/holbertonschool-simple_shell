#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * _err - checks and handles errors
 * @args: arguments to check
 * Return: void
 */
void _err(char *args[])
{
    fprintf(stderr, "%s: command not found\n", args[0]);
    free(args[0]);  // Free only the first argument (command)
    exit(98);
}

/**
 * exec - executes the input received
 * @args: arguments
 * @input: input
 * Return: void
 */
void exec(char **args, char *input)
{
    int status, statusExit;
    pid_t childPid = 0;

    if (access(args[0], X_OK) != 0)
        _err(args);

    childPid = fork();

    if (childPid == -1)
    {
        perror("fork");
        free(input);
        exit(0);
    }
    else if (childPid == 0)
    {
        execve(args[0], args, environ);
        perror("execve"); // If execve fails
        exit(0);
    }
    else
    {
        wait(&status);
        if (WIFEXITED(status))
        {
            statusExit = WEXITSTATUS(status);
            if (statusExit != 0)
            {
                free(args[0]);
                free(input);
                exit(0);
            }
        }
    }
}

/**
 * printEnv - print the environment variables
 * Return: void
 */
void printEnv(void)
{
    char **env;

    for (env = environ; *env != NULL; env++)
    {
        printf("%s\n", *env);
    }
}

/**
 * handle_path - searches for the command in directories listed in PATH
 * @command: the command to find
 * Return: full path of the command if found, NULL if not
 */
char *handle_path(char *command)
{
    char *path = getenv("PATH");
    char *token = strtok(path, ":");
    char *full_path = NULL;

    while (token != NULL)
    {
        full_path = malloc(strlen(token) + strlen(command) + 2); // +2 for "/" and NULL terminator
        if (full_path == NULL)
        {
            perror("malloc");
            exit(1);
        }
        strcpy(full_path, token);
        strcat(full_path, "/");
        strcat(full_path, command);

        if (access(full_path, X_OK) == 0) // Check if the command exists and is executable
        {
            return full_path;
        }
        free(full_path);
        token = strtok(NULL, ":");
    }

    return NULL; // Return NULL if command is not found in any of the directories in PATH
}

/**
 * tokenize - function that splits a string into multiple ones
 * @input: users input
 * @args: arguments
 * Return: void
 */
void tokenize(char *input, char *args[])
{
    char *token;
    unsigned int i = 0;

    token = strtok(input, " ");
    while (token != NULL)
    {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (args[0] == NULL)
        return; // Instead of exit(0), just return

    if (strcmp(input, "env") == 0)
    {
        printEnv();
        return;
    }

    if (strcmp(input, "exit") == 0 && args[1] == NULL)
    {
        free(args[0]);
        exit(0);
    }

    token = strdup(args[0]);
    args[0] = handle_path(args[0]);
    if (args[0] != NULL)
    {
        free(token);
        exec(args, input);
        free(args[0]);
        return;
    }
    free(token);
    fprintf(stderr, "%s: command not found\n", args[0]);
    exit(127);
}

/**
 * main - main function to run the shell
 * Return: 0 on success
 */
int main(void)
{
    char *input = NULL;
    size_t len = 0;
    char *args[100];
    ssize_t nread;

    while (1)
    {
        printf("$ ");
        nread = getline(&input, &len, stdin);
        if (nread == -1)
        {
            perror("getline");
            free(input);
            exit(0);
        }

        input[strcspn(input, "\n")] = 0; // Remove the newline character
        tokenize(input, args);
    }

    free(input);
    return (0);
}
