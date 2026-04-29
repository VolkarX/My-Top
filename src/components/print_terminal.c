/*
** EPITECH PROJECT, 2025
** G-PSU-100-MAR-1-1-mytop-15
** File description:
** print_terminal.c
*/

#include "../../include/my.h"

static void delay_echo_and_keypad(process_manager_t *mgr)
{
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    print_header();
    print_process(mgr);
}

static void handle_loop(options_t *options, process_manager_t *mgr)
{
    char ch;
    int delay = options->delay * 1000;
    int temp = 0;
    int check_interval = 50;

    while (true){
        if (temp >= delay) {
            clear();
            print_header();
            print_process(mgr);
            refresh();
            temp = 0;
        }
        ch = getch();
        if (ch == 'q' || ch == 'Q')
            break;
        napms(check_interval);
        temp += check_interval;
    }
}

void print_terminal(options_t *options, int temp, int check_interval)
{
    process_manager_t mgr = {.count = 0, .last_uptime = 0};

    initscr();
    delay_echo_and_keypad(&mgr);
    handle_loop(options, &mgr);
    endwin();
}
