#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LEN 1024

extern char **environ;

void execute_command(char **args, char *path);
void parse_command(char *u_command, char **args);
void process_commands(char *commands, char **commands_array);
void handle_commands_array(char **commands_array);
void handle_command(char *command);

/**
 * execute_command - func for executing command
 * @args: arguments to path
 * @path: path
 */
void execute_command(char **args, char *path)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (execve(path, args, environ) == -1)
        {
            free(path);
            fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if (wait(&status) == -1)
        {
            free(path);
            perror("wait failed");
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * parse_command - func for parsing command
 * @u_command: command to be parsed
 * @args: arguments to command
 */
void parse_command(char *u_command, char **args)
{
    char *command = strtok(u_command, " \t");
    int i = 0;

    while (command != NULL && i < MAX_LEN - 1)
    {
        args[i] = command;
        i++;
        command = strtok(NULL, " \t");
    }
    args[i] = NULL;
}

/**
 * process_commands - commands processor func
 * @commands: commands
 * @commands_array: array for all commands
 */
void process_commands(char *commands, char **commands_array)
{
    char *command;
    int a = 0;

    command = strtok(commands, "\n");
    while (command != NULL)
    {
        commands_array[a] = command;
        command = strtok(NULL, "\n");
        a++;
    }
    commands_array[a] = NULL;
}

/**
 * handle_commands_array - func for handling array of commands
 * @commands_array: array of commands
 */
void handle_commands_array(char **commands_array)
{
    int a = 0;
    char *command;

    while (commands_array[a] != NULL)
    {
        command = commands_array[a];
        if (strcmp(command, "exit") == 0)
            exit(0);
        else
            handle_command(command);
        a++;
    }
}

/**
 * handle_command - func for handling a single command
 * @command: command to handle
 */
void handle_command(char *command)
{
    char *args[MAX_LEN];
    char *path = strdup(command); /* Assume command is the path for simplicity */

    parse_command(command, args);
    execute_command(args, path);

    free(path);
}

/**
 * main - main func to process all functions
 * Return: integer
 */
int main(void)
{
    char commands[MAX_LEN];
    char *commands_array[MAX_LEN];
    ssize_t read_size;

    while (1)
    {
        write(STDOUT_FILENO, "$ ", 2);
        read_size = read(STDIN_FILENO, commands, MAX_LEN - 1);
        if (read_size == -1)
        {
            perror("Error reading command");
            exit(EXIT_FAILURE);
        }
        else if (read_size == 0)
            break;
        commands[read_size] = '\0';

        process_commands(commands, commands_array);
        handle_commands_array(commands_array);
    }
    return (0);
}
