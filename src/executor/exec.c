#include "minishell.h"

// /**
//  * @name: Outputs redirection
//  * @dev: Redirect the outputs in the different files specified for the current command.
//  * @outputs: Linked list of all the redirections.
//  * @from: File descriptor where the output of the command is written.
//  *
//  * @notice: If from is null then set the file descriptor to default standard output (1)
//  */
// static void out_redir(t_list *outputs, int *from)
// {
//     t_list *tmp;
//     t_redir *redir;
//     int fd;
//     char buffer[1024];
    
//     fd = from ? from[0] : 1;
//     while ( outputs && (read(fd, buffer, 1024) != EOF) )
//     {
//         tmp = outputs;
//         while (tmp)
//         {
//             redir = (t_redir *)tmp->content;
//             write(redir->fd, &buffer, 1024);
//             tmp = tmp->next;
//         }
//     }
// }

// /**
//  * @name: Inputs redirection
//  * @dev: Redirect the inputs to the current command.
//  * @inputs: Linked list of all the redirections.
//  */
// static void in_redir(t_list *inputs)
// {
//     t_redir *redir;
//     int fd;
    
//     while ( inputs  )
//     {
//         redir = (t_redir *) inputs->content;
//         fd = dup2(redir->fd, STDIN_FILENO);

//         if (fd < 0)
//             perror("Error redirecting to file");
//         if (fd > 0) 
//             close(redir->fd);

//         inputs = inputs->next;
//     }
// }

// static void read_from_pipe(int *from)
// {
//     if (from)
//     {
//         dup2(from[0], STDIN_FILENO);
//     }
// }

// static void write_to_pipe(int *to)
// {
//     if (to)
//     {
//         dup2(to[1], STDOUT_FILENO);
//         close(to[1]);
//     }
// }

// static void exec(t_cmd *cmds)
// {
//     in_redir(cmds->inputs);
//     read_from_pipe(cmds->from);
//     write_to_pipe(cmds->to);

//     execve(cmds->bin_path, cmds->args, environ);
//     exit(1);
// }
static void exec(t_cmd *cmds, int *currfd, int *prevfd)
{
    close(currfd[0]);

    if (prevfd)
    {
        dup2(prevfd[0], STDIN_FILENO);
        close(prevfd[0]);
        free(prevfd);
    }
    
    if (cmds->next)
    {
        dup2(currfd[1], STDOUT_FILENO);
        close(currfd[1]);
    }

    execve(cmds->bin_path, cmds->args, environ);
    exit(1);
}

// int exec_cmds(t_cmd *cmds)
// {
//     int status = 0;
//     pid_t pid;
    
//     if ( (pid = fork()) < 0 )
//     {
//         perror("fork");
//         return (1);
//     }
    
//     if (pid == 0)
//         exec(cmds);
//     else
//         wait(&status);

//     // printf("cmd: %s\n\n", cmds->bin_path);
//     out_redir(cmds->outputs, cmds->to);

//     return ( status );
// }
 
int exec_cmds(t_cmd *cmd, int *prevfd)
{
    pid_t       pid;
    int         *fd;

    fd = (int *) malloc(sizeof(int) * 2);
    if ( pipe(fd) < 0 )
    {
        free(fd);
        return (1);
    }
    if ( (pid = fork()) < 0 )
        return (1);
    
    // if buffer write to the read end of new file descriptor
    if (pid == 0)
        exec(cmd, fd, prevfd);

    wait(&cmd->status);
    char str[] = "Hello";

    write(fd[1], str, 5);
    close(fd[1]);
    
    if (cmd->next)
        return ( exec_cmds(cmd->next, fd) );
    else
    {
        close(fd[0]);
        free(fd);
        return ( cmd->status );
    }
}