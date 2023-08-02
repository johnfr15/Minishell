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

static void exec_redirection(t_cmd cmd, int *prevfd)
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
    
    if (cmd.next)
    {
        dup2(fds[1], STDOUT_FILENO);
        close(fds[1]);
    }

    execve(cmd.bin_path, cmd.args, environ);
    exit(0);
}

static void exec_cmd(t_cmd cmd)
{
    pid_t       pid;

    pid = fork();
    
    // if buffer write to the read end of new file descriptor
    if (pid == 0)
    {
        if ( cmd.outputs || cmd.inputs || cmd.errs )
            exec_redirection(cmd, NULL);
        else
            execve( cmd.bin_path, cmd.args, environ );
    }
    wait(&cmd.status);
    SHELL.exitstatus = WIFEXITED(cmd.status) ? WEXITSTATUS(cmd.status) : -1;
}

static void exec_builtin(t_cmd cmd)
{
    // if ( ft_strcmp(cmd.bin_path, "echo") == 0 ) echo();
    if ( ft_strcmp(cmd.bin_path, "cd") == 0 ) cd(cmd);
    // if ( ft_strcmp(SHELL->table->ast->bin_path, "pwd") == 0 ) pwd();
    // if ( ft_strcmp(SHELL->table->ast->bin_path, "export") == 0 ) export();
    // if ( ft_strcmp(SHELL->table->ast->bin_path, "unset") == 0 ) unset();
    // if ( ft_strcmp(SHELL->table->ast->bin_path, "env") == 0 ) env();
    if ( ft_strcmp(cmd.bin_path, "exit") == 0 ) exit(0);
}

void exec(t_cmd *cmds)
{
    while (cmds)
    {
        // print_cmd(cmds);

        if (cmds->is_builtin)   exec_builtin(*cmds);
        else                    exec_cmd(*cmds);

        cmds = cmds->next;
    }
}