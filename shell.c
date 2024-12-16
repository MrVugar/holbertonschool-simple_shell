#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>  // wait funksiyasını əlavə edin

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    char *args[2];

    while (1)
    {
        /* Göstərici (prompt) */
        printf("simple_shell> ");
        fflush(stdout);

        /* Komanda oxumaq */
        nread = getline(&line, &len, stdin);
        if (nread == -1)  /* EOF */
        {
            free(line);
            exit(0);
        }

        /* Yeni xətt simvolunu silmək */
        line[strcspn(line, "\n")] = 0;

        /* Komanda yoxlanılması */
        if (strcmp(line, "exit") == 0)
        {
            free(line);
            exit(0);
        }

        /* Fork yaradın */
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            continue;
        }
        else if (pid == 0)
        {
            /* İcra ediləcək komanda */
            args[0] = line;
            args[1] = NULL;

            if (execve(line, args, NULL) == -1)
            {
                perror("Error");
                exit(1);
            }
        }
        else
        {
            /* Uşağın bitməsini gözləyin */
            wait(NULL);
        }
    }

    return 0;
}
