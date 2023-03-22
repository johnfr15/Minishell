#include "minishell.h"

void move_cursor_left() {
    char *left_cursor;
    if ((left_cursor = tgetstr("le", NULL)) == NULL) {
        perror("tgetstr");
        exit(1);
    }
    fputs(left_cursor, stdout);
}

void move_cursor_right() {
    char *right_cursor;
    if ((right_cursor = tgetstr("nd", NULL)) == NULL) {
        perror("tgetstr");
        exit(1);
    }
    fputs(right_cursor, stdout);
}

void move_cursor_to_start() {
    char *cursor_home;
    if ((cursor_home = tgetstr("cr", NULL)) == NULL) {
        perror("tgetstr");
        exit(1);
    }
    fputs(cursor_home, stdout);
}

void clear_line() {
    char *clr_eol;
    if ((clr_eol = tgetstr("ce", NULL)) == NULL) {
        perror("tgetstr");
        exit(1);
    }
    fputs(clr_eol, stdout);
}

void print_prompt() {
    printf(">> ");
    fflush(stdout);
}


void insert_char(char c) {
    if (buffer_pos >= MAX_BUF_SIZE - 1) {
        return;
    }
    putchar(c);
    fflush(stdout);
    buffer[buffer_pos++] = c;
}


void delete_char() {
    if (buffer_pos == 0) {
        return;
    }
    buffer_pos--;
    move_cursor_left();
    clear_line();
    buffer[buffer_pos] = '\0';
    printf("%s", buffer);
    fflush(stdout);
}