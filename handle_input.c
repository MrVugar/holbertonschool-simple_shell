#include "shell.h"

void handle_input(char *input)
{
    if (input == NULL)
    {
        return;
    }
    execute_command(input);
}
