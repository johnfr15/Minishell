#include "minishell.h"

char **tokenization(char *cmd)
{
    char **tokens = ft_split_del(cmd, " \n\t");
    
    return (tokens);
}