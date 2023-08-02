#include "minishell.h"

int cd(t_cmd *cmd, char *cwd)
{
    if ( chdir(cmd->args[1]) != 0 )
    {
        perror("Error changing directory");
        return (1);
    }
    cwd = getcwd(NULL, BUFFER_SIZE);
    cwd = basename(cwd);

    return (0);
}