# Simple Shell Project

This project is a simple implementation of a Unix-like shell, a command-line interpreter that allows users to interact with the operating system. It's a project undertaken as part of the Holberton School curriculum.

## Functionality

This shell is capable of:

*   **Executing commands:** Takes user input, parses it, and executes the corresponding command.
*   **Handling built-in commands:** Implements basic built-in commands such as `exit`, `env`, and `cd`.
*   **Handling arguments:** Passes arguments to executables.
*   **Path resolution:** Searches the PATH environment variable to locate executables if a full path isn't given.
*   **Error handling:** Provides basic error messages for invalid commands and system errors.
*   **Basic prompt:** Displays a prompt to the user, allowing for interactive use.

## Compilation

To compile the project, use the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
