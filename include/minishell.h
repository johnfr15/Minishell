#ifndef MINISHELL_H
# define MINISHELL_H

// Color
#define RED     "\033[31;1m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

# include "stdbool.h"
# include <libgen.h>
# include <signal.h>
# include <term.h>
# include <errno.h>
# include <termios.h>
# include <sys/wait.h>
# include <dirent.h>
# include "fcntl.h"
# include "string.h"
# include "stdlib.h"
# include "unistd.h"
# include "stdio.h"
# include "libft.h"

extern char **environ;

typedef struct  s_hist
{
	int				nbr;
	char			*cmd_line;
	struct s_hist	*prev;
	struct s_hist	*next;
}               t_hist;

typedef struct s_shell
{
    char    *cwd;
    char    *user;
    char    *hostname;
    char    *input;
    char    **tokens;
    t_hist  *history;
    char    **bin_path;
    struct termios *termios;
}              t_shell;
t_shell shell;

/*
 ** termcap.c 
 */
void	init_terminal_data(char *termtype);

/*
 ** init.c
*/
void init(t_shell *shell);

/*
 ** error.c
 */
int error(int status);

/*
 ** history.c
 */
t_hist *add_history(t_hist *hist, char *cmd);

/*
 ** lexer.c
 */
char **tokenization(char *cmd);

/*
 ** exec.c
*/
int exec_cmd(char **tokens, char **env_path);

#endif