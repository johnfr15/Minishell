#include "minishell.h"

t_hist *add_history(t_hist *hist, char *cmd)
{
    t_hist *new_hist = malloc(sizeof(t_hist));

    new_hist->nbr = hist->nbr + 1;
    new_hist->cmd_line = ft_strdup(cmd);
    new_hist->prev = hist;
    new_hist->next = NULL;

    hist->next = new_hist;
    
    return (new_hist);
}

/*
void navigate_history(int direction) {
    if (direction == -1 && history_count == 0) {
        return;
    }
    if (direction == 1 && buffer_pos == 0) {
        return;
    }
    static int history_pos = 0;
    if (direction == -1) {
        if (history_pos > 0) {
            history_pos--;
        }
    } else {
        if (history_pos < history_count - 1) {
            history_pos++;
        }
    }
    clear_line();
    move_cursor_to_start();
    if (direction == -1 && history_pos == 0) {
        buffer[0] = '\0';
        buffer_pos = 0;
    } else {
        strcpy(buffer, history[history_pos]);
        buffer_pos = strlen(buffer);
    }
    printf("%s", buffer);
    fflush(stdout);
}
*/