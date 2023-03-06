#include "minishell.h"

t_hist *add_history(t_hist *hist, char *cmd)
{
    t_hist *new_hist = malloc(sizeof(t_hist));

    new_hist->nbr = hist->nbr + 1;
    new_hist->cmd_line = ft_strdup(cmd);
    new_hist->prev = hist;
    new_hist->next = NULL;

    hist->next = new_hist;
    
    return (new_hist);
}