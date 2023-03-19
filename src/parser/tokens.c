#include "minishell.h"

void    parse_word(t_cmd *cmd, char *arg)
{
    t_list *new = ft_lstnew( arg );

    if ( cmd->args == NULL )
    {
        cmd->bin_path = find_bin_path( arg, shell.bin_paths, 0 );
        cmd->args = new;
    }
    else
        ft_lstadd_back( &cmd->args, new );
}

void    parse_pipe(t_cmd **cmd)
{
    int pipes[2];
    t_list *curr_pipe;
    t_list *next_pipe;

    (*cmd)->next = new_cmd();

    if (pipe(pipes) == -1) 
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    curr_pipe = ft_lstnew( &pipes[1] );
    next_pipe = ft_lstnew( &pipes[0] );

    ft_lstadd_back( &(*cmd)->outputs, curr_pipe );
    ft_lstadd_back( &(*cmd)->next->inputs, next_pipe );

    *cmd = (*cmd)->next;
}

void    parse_less(t_cmd *cmd, t_tokens **tokens)
{
   char *file_path;
    int *fd;
    t_list *newout;

    if ( (*tokens = (*tokens)->next) == NULL)
    {
        perror("output");
        exit(EXIT_FAILURE);
    }

    file_path = (*tokens)->arg;
    fd = (int *) malloc(sizeof(int));

    if ( (*tokens)->token != WORD )
        error( 4, file_path );

    if ( (*fd = open( file_path, O_RDWR | O_CREAT, 0600 )) == -1)
    {
        perror( file_path );
        exit(EXIT_FAILURE);
    }

    newout = ft_lstnew( fd );
    if ( cmd->inputs == 0 )
        cmd->inputs = newout;
    else
        ft_lstadd_back( &cmd->inputs, newout );
}

void    parse_great(t_cmd *cmd, t_tokens **tokens)
{
    char *file_path;
    int *fd;
    t_list *newout;

    if ( (*tokens = (*tokens)->next) == NULL)
    {
        perror("output");
        exit(EXIT_FAILURE);
    }

    file_path = (*tokens)->arg;
    fd = (int *) malloc(sizeof(int));

    if ( (*tokens)->token != WORD )
        error( 4, file_path );

    if ( (*fd = open( file_path, O_RDWR | O_CREAT, 0600 )) == -1)
    {
        perror( file_path );
        exit(EXIT_FAILURE);
    }

    newout = ft_lstnew( fd );
    if ( cmd->outputs == 0 )
        cmd->outputs = newout;
    else
        ft_lstadd_back( &cmd->outputs, newout );
}

void    parse_twogreat(t_cmd *cmd, t_tokens **tokens)
{
   char *file_path;
    int *fd;
    t_list *newout;

    if ( (*tokens = (*tokens)->next) == NULL)
    {
        perror("output");
        exit(EXIT_FAILURE);
    }

    file_path = (*tokens)->arg;
    fd = (int *) malloc(sizeof(int));

    if ( (*tokens)->token != WORD )
        error( 4, file_path );

    if ( (*fd = open( file_path, O_RDWR | O_CREAT, 0600 )) == -1)
    {
        perror( file_path );
        exit(EXIT_FAILURE);
    }

    newout = ft_lstnew( fd );
    if ( cmd->errs == 0 )
        cmd->errs = newout;
    else
        ft_lstadd_back( &cmd->errs, newout );
}