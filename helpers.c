#include <stdio.h>    /* getline, stdin */
#include <stdlib.h>   /* free, exit, EXIT_SUCCESS */
#include <string.h>   /* strcspn */
#include <unistd.h>   /* write, STDOUT_FILENO */

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

