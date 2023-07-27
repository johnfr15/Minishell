#include "minishell.h"

void create_table(t_tokens *tokens, t_cmd *ast)
{
    if (tokens == 0) return ;                 // Escape condition if tokens list is finnish

    int TOKEN = tokens->token;

    if (TOKEN == WORD)          parse_word(ast, tokens->arg);
    if (TOKEN == PIPE)          parse_pipe(&ast);
    if (TOKEN == LESS)          parse_redir(&ast->outputs, &tokens);
    if (TOKEN == GREAT)         parse_redir(&ast->inputs, &tokens);
    if (TOKEN == GREATGREAT)    parse_redir(&ast->outputs, &tokens);
    if (TOKEN == TWOGREAT)      parse_redir(&ast->errs, &tokens);

    create_table(tokens->next, ast);
}

void    resolve_args(t_cmd *cmds)
{
    char **args;
    t_list *head;
    int i;

    while (cmds)
    {
        i = 0;
        args = (char **) malloc(sizeof(char *) * (ft_lstsize(cmds->lst_args) + 1));
        head = cmds->lst_args;

        while (cmds->lst_args)
        {
            args[i] = cmds->lst_args->content;
            cmds->lst_args = cmds->lst_args->next;
            i++;
        }
        args[i] = NULL;

        cmds->lst_args = head;
        cmds->args = args;
        cmds = cmds->next;
    }
}