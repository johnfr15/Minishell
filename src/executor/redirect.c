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