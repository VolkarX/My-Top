/*
** EPITECH PROJECT, 2025
** G-PSU-100-MAR-1-1-mytop-15
** File description:
** get_cpu_stats.c
*/

#include "../../include/my.h"

static int skip(char *line, int i)
{
    while (line[i] == ' ')
        i++;
    return i;
}

static int parse_number(char *line, int i, unsigned long *value)
{
    *value = 0;
    while (isnum(line[i]) == true) {
        *value = *value * 10 + (line[i] - '0');
        i++;
    }
    return i;
}

static void parse_line(char *buffer, unsigned long *values)
{
    char *line = strstr(buffer, "cpu ");
    int i = 0;
    int j = 0;

    if (line == NULL)
        return;
    line += 4;
    for (j = 0; j < 10; j++) {
        i = skip(line, i);
        i = parse_number(line, i, &values[j]);
    }
}

static float calcul_perc(unsigned long value, unsigned long total)
{
    if (total == 0)
        return 0.0;
    return (value * 100.0) / total;
}

static void calcul_cpu_perc(unsigned long *values, cpu_stats_t *stats)
{
    unsigned long total = values[0] + values[1] + values[2] + values[3];
    unsigned long total2 = values[4] + values[5] + values[6] + values[7];

    total = total + total2;
    stats->us = calcul_perc(values[0], total);
    stats->sy = calcul_perc(values[2], total);
    stats->ni = calcul_perc(values[1], total);
    stats->id = calcul_perc(values[3], total);
    stats->wa = calcul_perc(values[4], total);
    stats->hi = calcul_perc(values[5], total);
    stats->si = calcul_perc(values[6], total);
    stats->st = calcul_perc(values[7], total);
}

void get_cpu_stats(cpu_stats_t *stats)
{
    char *buffer = malloc(sizeof(char) * 4096);
    FILE *fd = fopen("/proc/stat", "r");
    unsigned long values[10] = {0};

    if (fd == NULL || buffer == NULL)
        return;
    fread(buffer, 4096, 1, fd);
    fclose(fd);
    parse_line(buffer, values);
    calcul_cpu_perc(values, stats);
    free(buffer);
}
