#include "minishell.h"

int cd(t_cmd cmd)
{
    if ( chdir(cmd.args[1]) != 0 )
    {
        perror("Error changing directory");
        return (1);
    }
    SHELL.cwd = getcwd(NULL, BUFFER_SIZE);
    SHELL.cwd = basename(SHELL.cwd);

    return (0);
}