#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

extern char **environ; // Declare environ

int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];
    pid_t pid;
    int status, arg_count;
    char *token;
    char *prompt = "#cisfun$ ";

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("%s", prompt);

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            if(isatty(STDIN_FILENO))
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
       
         pid = fork();

        if (pid == -1) {
           perror("fork");
           exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (execve(args[0], args, environ) == -1)
            {
                perror("./shell");
                exit(EXIT_FAILURE);
            }
        } else {
             // Parent process
             if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
        }
    }
    return (EXIT_SUCCESS);
}
