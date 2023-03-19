#include "minishell.h"

void create_table(t_table_cmd *table, t_tokens *tokens, t_cmd *ast)
{
    if (tokens == 0) return ;                 // Escape condition if tokens list is finnish or 

    int TOKEN = tokens->token;
    
    if (TOKEN == WORD)          parse_word(ast, tokens->arg);
    if (TOKEN == PIPE)          parse_pipe(&ast);
    if (TOKEN == LESS)          parse_less(ast, &tokens);
    if (TOKEN == GREAT)         parse_great(ast, &tokens);
    if (TOKEN == GREATGREAT)    parse_great(ast, &tokens);
    if (TOKEN == TWOGREAT)      parse_twogreat(ast, &tokens);

    create_table(table, tokens->next, ast);
}