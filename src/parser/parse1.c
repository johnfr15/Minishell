#include "minishell.h"

void    parse_word(t_cmd *cmd, char *arg)
{
    t_list *new;

    if ( cmd->bin_path == NULL )
    {
        cmd->bin_path = find_bin_path( arg, shell.bin_paths, 0 );
        cmd->lst_args = ft_lstnew( cmd->bin_path );
    }
    else
    {
        new = ft_lstnew( arg );
        ft_lstadd_back( &cmd->lst_args, new );
    }
}

void    parse_pipe(t_cmd **lst_cmds)
{
    t_cmd *cmd = *lst_cmds;

    cmd->next = new_cmd();
    cmd->next->prev = cmd;

    *lst_cmds = cmd->next;
}

void    parse_builtin(t_cmd *cmd, char *arg)
{
    cmd->bin_path = arg;
    cmd->lst_args = ft_lstnew( cmd->bin_path );
    cmd->is_builtin = true;
}

void    parse_env(t_cmd *cmd, char *arg)
{
    char *env = getenv(arg + 1);
    t_list *new;

    if ( cmd->bin_path == NULL )
    {
        cmd->bin_path = find_bin_path( env, shell.bin_paths, 0 );;
        cmd->lst_args = ft_lstnew( cmd->bin_path );
    }
    else
    {
        new = ft_lstnew( env );
        ft_lstadd_back( &cmd->lst_args, new );
    }
}