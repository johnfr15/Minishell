#include "minishell.h"

static bool is_valid_token(t_tokens *token)
{
    if ( token == NULL)
    {
        perror("output");
        return (0);
    }
    return (1);
}

static t_redir *populate_redir(t_tokens *token)
{
    char *path;
    t_redir *redir;

    path = token->arg;
    if ( token->token != WORD )
        error( 4, path );

    redir = new_redir();
    redir->file_path = path;

    if ( (redir->fd = creat( path, 0600 )) == -1)
    {
        perror( path );
        exit(EXIT_FAILURE);
    }
    return (redir);
}

static void add_redir(t_list **lst_redir, t_redir *redir)
{
    t_list *new;

    new = ft_lstnew( redir );
    if ( *lst_redir == 0 )
        *lst_redir = new;
    else
        ft_lstadd_back( lst_redir, new );
}

void    parse_redir(t_list **lst_redir, t_tokens **tokens)
{
    t_redir *redir;

    *tokens = (*tokens)->next;
    if ( !is_valid_token(*tokens) )
        return ;

    redir = populate_redir(*tokens);
    add_redir(lst_redir, redir);
}