#include "minishell.h"

void clear_tokens(t_tokens  *tokens)
{
    t_tokens *tmp = 0;

    while (tokens)
    {
        tmp = tokens->next;
        tokens->arg = NULL;
        tokens->token = 0;

        free(tokens->arg);
        free(tokens);

        tokens = tmp;
    }
}

void clear_ast(t_cmd    *ast)
{
    t_cmd *tmp = 0;

    while (ast->next) ast = ast->next;

    while (ast->prev)
    {
        tmp = ast->prev;

        ft_memset(ast, 0, sizeof(t_cmd));
        free(ast->bin_path);
        free(ast->args);
        free(ast->output);
        free(ast->pipe);
        free(ast->lst_args);
        free(ast->outputs);
        free(ast->inputs);
        free(ast->errs);
        free(ast);

        ast = tmp;
    }
    ft_memset(ast, 0, sizeof(t_cmd));
}

void clear_table(t_table_cmd *table)
{
    clear_tokens(table->tokens);
    clear_ast(table->ast);
}