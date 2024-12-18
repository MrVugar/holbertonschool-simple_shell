#include "shell.h"

int main(void)
{
    char *input = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1)
    {
        write(STDOUT_FILENO, "$ ", 2);
        nread = getline(&input, &len, stdin);
        if (nread == -1)
        {
            if (feof(stdin))
                break;
            perror("getline");
            continue;
        }
        handle_input(input);
    }
    free(input);
    return (0);
}
