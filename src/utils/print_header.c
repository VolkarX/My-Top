/*
** EPITECH PROJECT, 2025
** G-PSU-100-MAR-1-1-mytop-15
** File description:
** print_header.c
*/

#include "../../include/my.h"

static void print_first_line(void)
{
    double load[3];
    coma_t float_division;
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    if (my_getloadavg(load, 3, 0) == -1)
        exit(84);
    printw("my_top - %d:%d:%d ", t->tm_hour, t->tm_min, t->tm_sec);
    print_uptime(0, &float_division);
    printw(" %d user,  ", count_users());
    printw("load average: %.2f, %.2f, %.2f\n", load[0], load[1], load[2]);
}

static void header_first_part(task_stats_t *stats)
{
    print_first_line();
    printw("Tasks: ");
    attron(A_BOLD);
    printw("%d ", stats->total);
    attroff(A_BOLD);
    printw("total,   ");
    attron(A_BOLD);
    printw("%d ", stats->running);
    attroff(A_BOLD);
    printw("running, ");
    attron(A_BOLD);
}

static void header_second_part(task_stats_t *stats, cpu_stats_t *cpu)
{
    printw("%d ", stats->sleeping);
    attroff(A_BOLD);
    printw("sleeping,   ");
    attron(A_BOLD);
    printw("%d ", stats->stopped);
    attroff(A_BOLD);
    printw("stopped,   ");
    attron(A_BOLD);
    printw("%d ", stats->zombie);
    attroff(A_BOLD);
    printw("zombie\n%%Cpu(s):  ");
    attron(A_BOLD);
    printw("%.1f ", cpu->us);
    attroff(A_BOLD);
    printw("us,  ");
    attron(A_BOLD);
    printw("%.1f ", cpu->sy);
    attroff(A_BOLD);
    printw("sy,  ");
    attron(A_BOLD);
}

static void header_third_part(cpu_stats_t *cpu)
{
    printw("%.1f ", cpu->ni);
    attroff(A_BOLD);
    printw("ni, ");
    attron(A_BOLD);
    printw("%.1f ", cpu->id);
    attroff(A_BOLD);
    printw("id,  ");
    attron(A_BOLD);
    printw("%.1f ", cpu->wa);
    attroff(A_BOLD);
    printw("wa,  ");
    attron(A_BOLD);
    printw("%.1f ", cpu->hi);
    attroff(A_BOLD);
    printw("hi,  ");
    attron(A_BOLD);
    printw("%.1f ", cpu->si);
    attroff(A_BOLD);
    printw("si,  ");
    attron(A_BOLD);
}

static void header_fourth_part(cpu_stats_t *cpu)
{
    printw("%.1f ", cpu->st);
    attroff(A_BOLD);
    printw("st\n");
    print_memory();
}

static void header_white_line(void)
{
    attron(A_STANDOUT);
    printw("    PID USER      PR  NI    VIRT    RES    SHR S  %%CPU  ");
    printw("%%MEM     TIME+ COMMAND                                          ");
    printw("                      ");
    attroff(A_STANDOUT);
    printw("\n");
}

void print_header(void)
{
    task_stats_t stats;
    cpu_stats_t cpu;

    get_task_stats(&stats);
    get_cpu_stats(&cpu);
    header_first_part(&stats);
    header_second_part(&stats, &cpu);
    header_third_part(&cpu);
    header_fourth_part(&cpu);
    header_white_line();
}
