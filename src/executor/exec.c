#include "minishell.h"

static int *new_pipe()
{
    int *fds = (int *) malloc(sizeof(int) * 2);
    if ( pipe(fds) < 0 )
    {
        free(fds);
        return NULL;
    }
    return (fds);
}

static void exec_redirection(t_cmd *cmd, int *prevfd)
{
    int         *fds;

    if ( (fds = new_pipe()) == NULL)
        return ;

    close(fds[0]);

    if (prevfd)
    {
        dup2(prevfd[0], STDIN_FILENO);
        close(prevfd[0]);
        free(prevfd);
    }
    
    if (cmd->next)
    {
        dup2(fds[1], STDOUT_FILENO);
        close(fds[1]);
    }

    execve(cmd->bin_path, cmd->args, environ);
    exit(0);
}

int exec_cmds(t_cmd *cmds)
{
    pid_t       pid;

    if ( (pid = fork()) < 0 )
        return (1);
    
    // if buffer write to the read end of new file descriptor
    if (pid == 0)
    {
        if ( cmds->outputs || cmds->inputs || cmds->errs )
            exec_redirection(cmds, NULL);
        else
            execve( cmds->bin_path, cmds->args, environ );
    }
    wait(&cmds->status);

    if (cmds->next)
        return ( exec_cmds(cmds->next) );
    else
        return ( cmds->status );
}

void exec_builtin(t_shell *shell)
{
    if ( ft_strcmp(shell->table->ast->bin_path, "cd") == 0 ) cd(shell->table->ast, shell->cwd);
    if ( ft_strcmp(shell->table->ast->bin_path, "exit") == 0 ) exit(0);
}