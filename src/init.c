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

void init(t_shell *shell)
{
    shell->cwd = init_cwd();
    shell->user = getenv("USER");
    shell->hostname = init_hostname();
    shell->input = init_input();
    shell->history = init_history();
    shell->bin_path = init_bin_path();
    tcgetattr(STDIN_FILENO, shell->termios);
}