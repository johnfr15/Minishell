#include "minishell.h"

static char *init_cwd()
{
    char *cwd = getcwd(NULL, 0);
    cwd = basename(cwd);

    return (cwd);
}

static char *init_hostname()
{
    char *hostname = malloc(BUFFER_SIZE);

    gethostname(hostname, BUFFER_SIZE);
    return (hostname);
}

static char *init_input()
{
    char *input =  malloc(BUFFER_SIZE);

    ft_bzero(input, BUFFER_SIZE);
    return (input);
}

static t_hist *init_history()
{
    t_hist *history = malloc(sizeof(t_hist));

    ft_bzero(history, sizeof(t_hist));
    return (history);
}

static char **init_bin_path()
{
    char *env_path = getenv("PATH");
    char **path = ft_split(env_path, ':');

    return (path);
}

static t_table_cmd *init_table_cmd()
{
    t_table_cmd *table = (t_table_cmd *) malloc(sizeof(t_table_cmd));

    table->tokens = NULL;
    table->ast = new_cmd();
    table->background = false;

    return table;
}

void init(t_shell *shell)
{
    shell->cwd = init_cwd();
    shell->user = getenv("USER");
    shell->hostname = init_hostname();
    shell->input = init_input();
    shell->history = init_history();
    shell->bin_paths = init_bin_path();
    shell->table = init_table_cmd();
    tcgetattr(STDIN_FILENO, shell->termios);
}

t_tokens    *new_token()
{
    t_tokens *token = (t_tokens *) malloc(sizeof(t_tokens));

    if (token == NULL)
        return (NULL);
        
    ft_memset(token, 0, sizeof(t_tokens));
    token->arg = NULL;
    token->next = NULL;

    return (token);
}

t_cmd    *new_cmd()
{
    t_cmd *cmd = (t_cmd *) malloc(sizeof(t_cmd));

    if (cmd == NULL)
        return (NULL);

    ft_memset(cmd, 0, sizeof(t_cmd));

    cmd->args = NULL;
    cmd->outputs = NULL;
    cmd->inputs = NULL;
    cmd->errs = NULL;
    cmd->bin_path = NULL;
    cmd->next = NULL;

    return (cmd);
}