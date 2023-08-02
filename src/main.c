#include "minishell.h"

int prompt(void) 
{
    int input_l;

    ft_bzero(SHELL.input, BUFFER_SIZE);
    ft_printf(GREEN "%s@%s" RESET ":" RED "%s" RESET "$ ", SHELL.user, SHELL.hostname, SHELL.cwd);

    if ( (input_l = read(STDIN_FILENO, SHELL.input, BUFFER_SIZE)) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    SHELL.input[input_l - 1] = '\0';

    // Execute cmd and refresh prompt's input
    if ( is_valid_input(SHELL.input) )
    {
        SHELL.history = add_history(SHELL.history, SHELL.input);
        return (1);
    }
    return (0);
}

int main(int argc, char **argv, char **environ)
{
    (void)argc;
    (void)argv;
    (void)environ;

    init(&SHELL);

    while (1)
    {
        // Get the input from user
        if (prompt() == 0)
            continue;
        
        // lexer and parser
        SHELL.table->tokens = tokenization(SHELL.input);
        resolve_meta_char(SHELL.table->tokens);
        create_table(SHELL.table->tokens, SHELL.table->ast);
        resolve_args(SHELL.table->ast);
        
        // Execute 
        if (SHELL.table->ast->is_builtin)
            exec_builtin(&SHELL);
        else
            exec_cmds(SHELL.table->ast);

        // Clear everything
        clear_table(SHELL.table);
    }
    return (EXIT_SUCCESS);
}