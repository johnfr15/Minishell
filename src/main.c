#include "minishell.h"

int prompt(void) 
{
    int input_l;

    ft_bzero(shell.input, BUFFER_SIZE);
    ft_printf(GREEN "%s@%s" RESET ":" RED "%s" RESET "$ ", shell.user, shell.hostname, shell.cwd);

    if ( (input_l = read(STDIN_FILENO, shell.input, BUFFER_SIZE)) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    shell.input[input_l - 1] = '\0';

    // Execute cmd and refresh prompt's input
    if ( is_valid_input(shell.input) )
    {
        shell.history = add_history(shell.history, shell.input);
        return (1);
    }
    return (0);
}

int main()
{
    init(&shell);

    while (1)
    {
        // Get the input from user
        if (prompt() == 0)
            continue;
        
        // lexer and parser
        shell.table->tokens = tokenization(shell.input);
        create_table(shell.table->tokens, shell.table->ast);
        resolve_args(shell.table->ast);
        
        // Execute 
        if (shell.table->ast->is_builtin)
            exec_builtin(&shell);
        else
            exec_cmds(shell.table->ast);

        // Clear everything
        clear_table(shell.table);
    }
    return (EXIT_SUCCESS);
}