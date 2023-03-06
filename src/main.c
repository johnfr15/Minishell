#include "minishell.h"

int prompt(void) 
{
    ft_bzero(shell.input, BUFFER_SIZE);
    ft_printf(GREEN "%s@%s" RESET ":" RED "%s" RESET "$ ", shell.user, shell.hostname, shell.cwd);

    if (read(STDIN_FILENO, shell.input, BUFFER_SIZE) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    size_t input_l = ft_strlen(shell.input);

    // Execute cmd and refresh prompt's input
    if (input_l > 1)
    {
        shell.history = add_history(shell.history, shell.input);
        shell.input[input_l - 1] = '\0';
        return (1);
    }
    return (0);
}

int main()
{
    init(&shell);

    while (1)
    {
        if (prompt() == 0)
            continue;
        
        shell.tokens = tokenization(shell.input);
        exec_cmd(shell.tokens, shell.bin_path);
    }
    return (EXIT_SUCCESS);
}