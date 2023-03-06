#include "minishell.h"

int error(int status)
{
    if (status == 1)
        printf("tgetent: Could not access the termcap data base\n");
    if (status == 2)
        printf("tgetent: Terminal type is not defined in termcap library\n");
    exit(1);
}