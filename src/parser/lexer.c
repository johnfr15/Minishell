#include "minishell.h"

t_tokens *tokenization(char *cmd)
{
    t_tokens *head = new_token();
    t_tokens *tmp = head;
    int i = 0;
    char **tokens = ft_split_del(cmd, " \n\t");

    while (tokens[i])
    {
        tmp->arg = tokens[i];

        if      (ft_strcmp(tokens[i], "|") == 0)  tmp->token = PIPE;
        else if (ft_strcmp(tokens[i], "<") == 0)  tmp->token = LESS;
        else if (ft_strcmp(tokens[i], ">") == 0)  tmp->token = GREAT;
        else if (ft_strcmp(tokens[i], ">>") == 0) tmp->token = GREATGREAT;
        else if (ft_strcmp(tokens[i], "2>") == 0) tmp->token = TWOGREAT;
        else if (*tokens[i] >= 32 && *tokens[i] <= 126) tmp->token = WORD;
        else printf("token is not an ascii charactere\n");

        if (tokens[i + 1])
            tmp->next = new_token();

        tmp = tmp->next;
        i++;
    }
    
    return (head);
}
