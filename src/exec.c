#include "minishell.h"

static char *resolve_path(char *s1, char *s2)
{
    char *tmp1;
    char *tmp2;

    tmp1 = ft_strjoin(s1, "/");
    tmp2 = ft_strjoin(tmp1, s2);

    return (tmp2);
}

static int is_cmd(char *cmd, DIR *dir)
{
    struct dirent *entry;

    if ( (entry = readdir(dir)) == NULL ) 
        return (0);
    
    if (ft_strcmp(entry->d_name, cmd) == 0)
        return (1);

    return (is_cmd( cmd, dir));
}

static char *find_bin_path(char *cmd, char **path, int depth)
{
    DIR *dir;

    if (path[depth] == NULL)
        return (NULL);

    dir = opendir(path[depth]);

    if ( dir != NULL && is_cmd(cmd, dir) )
        return ( resolve_path(path[depth], cmd) );
    
    if (dir) closedir(dir);

    return ( find_bin_path(cmd, path, depth + 1) );
}

// static char **get_args(char **tokens)
// {
//     char **argv;
//     int i = 0;
//     while (tokens[i + 1])
//         i++;

//     argv = (char **) malloc(sizeof(char *) * (i + 1));
//     return (argv);
// }

int exec_cmd(char **tokens, char **bin_path)
{
    printf("Executing %s\n", tokens[0]);
    int status;
    char *path = find_bin_path(tokens[0], bin_path, 0);
    printf("Bin path: %s\n", path);
    char **argv = &tokens[1];
    printf("args: ");
    for (int i = 0; argv[i]; i++)
        printf("%s ", argv[i]);
    printf("\n");

    pid_t pid = fork();

    if (pid == 0)
        execve(path, argv, environ);
    else
        wait(&status);

    free(tokens);
    return (0);
}