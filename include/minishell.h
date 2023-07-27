#ifndef MINISHELL_H
# define MINISHELL_H

// Color
# define RED     "\033[31;1m"
# define GREEN   "\033[0;32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

# include "stdio.h"
# include "unistd.h"
# include "stdlib.h"
# include "string.h"
# include "fcntl.h"
# include "stdbool.h"
# include "libgen.h"
# include "signal.h"
# include "errno.h"
# include "termios.h"
# include "termcap.h"
# include "sys/wait.h"
# include <sys/stat.h>
# include "dirent.h"
# include "libft.h"
# include "tokens.h"

extern char **environ;

typedef struct  s_hist
{
	int				nbr;
	char			*cmd_line;
	struct s_hist	*prev;
	struct s_hist	*next;
}               t_hist;

typedef struct  s_cmd
{
    char            *bin_path;
    char            **args;
    char            *output;
    int             status;
    int             *pipe;
    t_list          *lst_args;
    t_list          *outputs;
    t_list          *inputs;
    t_list          *errs;
    struct s_cmd    *prev;
    struct s_cmd    *next;
}               t_cmd;

typedef struct  s_tokens
{
    enum Token      token;
    char            *arg;
    struct s_tokens *next;
}               t_tokens;

/**
* - ast: (abstract syntax tree) is the tree of commands that will be executed
*   it is build with the tokens generated vy the lexer.
*
* - in_file: the starting file argument used by the first command.
*
* - out_file: the file that will receive the final output.
*
* - err_file: the file where any errors ocurring during run time will write.
*
* - bacground: If the process need to be run in the background thus letting us
*   to continue interact with the shell command
*/
typedef struct  s_table_cmd
{
    t_tokens    *tokens;
    t_cmd       *ast;
    char        *pipebuffer;
    bool        background;     
}               t_table_cmd;

typedef struct  s_redir
{
    char *file_path;
    int fd;
}               t_redir;

typedef struct s_shell
{
    char        *cwd;
    char        *user;
    char        *hostname;
    char        **bin_paths;
    char        *input;
    t_hist      *history;
    t_table_cmd *table;
    struct termios *termios;

}              t_shell;
t_shell shell;


/*
 ** termcap.c
 * @notice: For Managing cursor when interacting with the prompt 
 */
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
int tcgetattr(int fd, struct termios *termios_p);
int tgetent(char *bp, const char *name);
int tgetflag(NCURSES_CONST char *id);
int tgetnum(NCURSES_CONST char *id);
char *tgetstr(NCURSES_CONST char *id, char **area);
char *tgoto(const char *cap, int col, int row);
int tputs(const char *str, int affcnt, int (*putc)(int));

/*
 ** init.c
*/
void        init(t_shell *shell);
t_tokens    *new_token();
t_cmd       *new_cmd();
t_redir     *new_redir();
int         is_valid_input(char *input);

/*
 ** error.c
 */
int error(int status, void *payload);

/*
 ** history.c
 */
t_hist *add_history(t_hist *hist, char *cmd);

/*
 ** lexer.c
 */
t_tokens *tokenization(char *cmd);

/**
 * parser
 */

void    create_table(t_table_cmd *table, t_tokens *tokens, t_cmd *ast);
void    resolve_args(t_cmd *cmds);
void    parse_word(t_cmd *cmd, char *arg);
void    parse_pipe(t_cmd **cmd);
void    parse_redir(t_list **lst_redir, t_tokens **tokens);


/*
 ** exec.c
*/
int exec_cmds(t_cmd *cmds, int *prevfd);


/*
 ** utils.c
*/
char *find_bin_path(char *cmd, char **paths, int depth);
void print_cmd(t_cmd *cmd);

#endif