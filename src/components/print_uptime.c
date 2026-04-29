/*
** EPITECH PROJECT, 2025
** G-PSU-100-MAR-1-1-mytop-15
** File description:
** get_uptime.c
*/

#include "../../include/my.h"

static float get_uptime(uptime_t *uptime)
{
    FILE *fd;
    char *buffer = malloc(256);
    float raw_uptime = 0.0;

    fd = fopen("/proc/uptime", "r");
    if (fd == NULL)
        return 0.0;
    fgets(buffer, 256, fd);
    buffer = strtok(buffer, " ");
    raw_uptime = atof(buffer);
    free(buffer);
    return raw_uptime;
}

static void get_before_and_after_coma(float number, coma_t *float_division)
{
    float_division->before_coma = (int)number;
    float_division->after_coma = number - float_division->before_coma;
}

static void less_than_24h_case(float raw_uptime,
    coma_t *float_division, float raw_minutes)
{
    int full_minutes = 0;

    get_before_and_after_coma(raw_uptime, float_division);
    raw_minutes = float_division->after_coma * 60;
    full_minutes = (int)raw_minutes;
    if (full_minutes >= 10)
        printw("up  %d:%d,  ", float_division->before_coma, full_minutes);
    if (full_minutes < 10)
        printw("up  %d:0%d,  ", float_division->before_coma, full_minutes);
}

static void more_than_24h_case(int full_days, float raw_uptime,
    coma_t *float_division, int full_minutes)
{
    full_days = (int)raw_uptime / 24;
    raw_uptime = raw_uptime - full_days;
    raw_uptime = raw_uptime * 24;
    get_before_and_after_coma(raw_uptime, float_division);
    full_minutes = (int)(float_division->after_coma * 60);
    printw("up  %d days,  %d:%d, ", full_days, float_division->before_coma,
        full_minutes);
}

void print_uptime(int full_days, coma_t *float_division)
{
    uptime_t *uptime = malloc(sizeof(uptime_t));
    float raw_uptime = get_uptime(uptime);
    int full_minutes = 0;

    if (raw_uptime < 60){
        printw("up  0 min,  ");
        return;
    }
    raw_uptime = raw_uptime / 60;
    if (raw_uptime < 60){
        printw("up  %d min, ", (int)raw_uptime);
        return;
    }
    raw_uptime = raw_uptime / 60;
    if (raw_uptime < 24){
        less_than_24h_case(raw_uptime, float_division, 0);
        return;
    }
    more_than_24h_case(full_days, raw_uptime, float_division, full_minutes);
    free(uptime);
}
