#include "minishell.h"

static char *resolve_env(char *token)
{
    char *tmp = ft_strdup(token);
    char *tmpEnv = ft_strdup(token);
    char *env = NULL;
    int i = 0;
    int j = 0;
    size_t len;

    while ( tmp[i] != '$' ) i++;
    tmp[i] = '\0';
    while ( ft_isupper(tmpEnv[i + j + 1]) ) j++;
    tmpEnv[i + 1 + j] = '\0';
    tmp[i + 1 + j - 1] = '\0';

    env = getenv(&tmpEnv[i + 1]);
    len = i + ft_strlen(env) + ft_strlen(&tmp[i + 1 + j + 1]);
    
    free(token);
    token = (char *) malloc( sizeof(char) * (len + 2) );
    ft_memset(token, 0, len + 1);

    ft_strlcat( token, tmp, (size_t) ft_strlen(tmp) + 1 );
    ft_strlcat( token, env, (size_t) ft_strlen(env) + ft_strlen(token) + 1 );
    ft_strlcat( token, &tmp[i + 1 + j], (size_t) ft_strlen(&tmp[i + 1 + j]) + ft_strlen(token) + 1 );

    free(tmp);

    return (token);
}

void    resolve_meta_char(t_tokens *tokens)
{
    if (tokens == NULL) return ;

    char *token = tokens->arg;
    int i = 0;

    while (token[i])
    {
        if (ft_strcmp(&token[i], "$?") == 0) tokens->arg = ft_itoa(SHELL.exitstatus);
        else if (token[i] == '$') tokens->arg = resolve_env(token);
        i++;
    }

    resolve_meta_char(tokens->next);
}