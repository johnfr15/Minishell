#include "minishell.h"

static char *resolve_path(char *s1, char *s2)
{
    char *tmp1;
    char *tmp2;

    tmp1 = ft_strjoin(s1, "/");
    tmp2 = ft_strjoin(tmp1, s2);
    free(tmp1);

    return (tmp2);
}

static int is_cmd(char *cmd, DIR *dir)
{
    struct dirent *entry;

    if ( (entry = readdir(dir)) == NULL )
        return (0);
    
    if ( ft_strcmp(entry->d_name, cmd) == 0 )
        return (1);

    return (is_cmd( cmd, dir ));
}

char *find_bin_path(char *cmd, char **paths, int depth)
{
    DIR *dir;

    if (paths[depth] == NULL)
        return (NULL);

    dir = opendir(paths[depth]);

    if ( dir != NULL && is_cmd(cmd, dir) )
        return ( resolve_path(paths[depth], cmd) );
    
    if (dir) closedir(dir);

    return ( find_bin_path(cmd, paths, depth + 1) );
}

void print_cmd(t_cmd *cmd)
{
    t_redir *redir;
    int i;

    printf("Path: %s\n", cmd->bin_path);

    printf("args: ");
    i = 0;
    while (cmd->args[i])
        printf("%s ", cmd->args[i++]);
    printf("\n");
    
    printf("Outputs: ");
    while (cmd->outputs)
    {
        redir = (t_redir *) cmd->outputs->content;
        printf("%d ", redir->fd);
        cmd->outputs = cmd->outputs->next;
    }
    printf("\n");

    printf("Intputs: ");
    while (cmd->inputs)
    {
        redir = (t_redir *) cmd->inputs->content;
        printf("%d ", redir->fd);
        cmd->inputs = cmd->inputs->next;
    }
    printf("\n");

    printf("errs: ");
    while (cmd->errs)
    {
        redir = (t_redir *) cmd->errs->content;
        printf("%d ", redir->fd);
        cmd->errs = cmd->errs->next;
    }
    printf("\n");


    printf("prev: %p\n", cmd->prev);
    printf("next: %p\n", cmd->next);
    printf("\n\n");

}