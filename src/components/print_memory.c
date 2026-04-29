/*
** EPITECH PROJECT, 2025
** G-PSU-100-MAR-1-1-mytop-15
** File description:
** print_memory.c
*/

#include "../../include/my.h"

static float parse_meminfo_value(char *buffer, char *key)
{
    char *line = strstr(buffer, key);
    int i = 0;
    int value = 0;

    if (line == NULL)
        return 0.0;
    while (isnum(line[i]) != true)
        i++;
    while (isnum(line[i]) == true) {
        value = value * 10 + (line[i] - '0');
        i++;
    }
    return value / 1024.0;
}

static void get_memory_infos(memory_stats_t *memory)
{
    char *buffer = malloc(sizeof(char) * 4096);
    FILE *fd = fopen("/proc/meminfo", "r");

    if (fd == NULL || buffer == NULL)
        return;
    fread(buffer, 4096, 1, fd);
    fclose(fd);
    memory->total = parse_meminfo_value(buffer, "MemTotal:");
    memory->free = parse_meminfo_value(buffer, "MemFree:");
    memory->available = parse_meminfo_value(buffer, "MemAvailable:");
    memory->buffers = parse_meminfo_value(buffer, "Buffers:");
    memory->cached = parse_meminfo_value(buffer, "Cached:");
    memory->sreclaimable = parse_meminfo_value(buffer, "SReclaimable:");
    memory->swap_total = parse_meminfo_value(buffer, "SwapTotal:");
    memory->swap_free = parse_meminfo_value(buffer, "SwapFree:");
    memory->used = memory->total - memory->free - memory->buffers
        - memory->cached;
    memory->swap_used = memory->swap_total - memory->swap_free;
    free(buffer);
}

static void print_memory_first_part(memory_stats_t *memory)
{
    printw("MiB Mem :  ");
    attron(A_BOLD);
    printw("%.1f ", memory->total);
    attroff(A_BOLD);
    printw("total,   ");
    attron(A_BOLD);
    printw("%.1f ", memory->free);
    attroff(A_BOLD);
    printw("free,   ");
    attron(A_BOLD);
    printw("%.1f ", memory->used);
    attroff(A_BOLD);
    printw("used,   ");
    attron(A_BOLD);
    printw("%.1f ", memory->buffers + memory->cached
        + memory->sreclaimable);
    attroff(A_BOLD);
}

void memory_second_part(memory_stats_t *memory)
{
    printw("buff/cache\nMiB Swap:   ");
    attron(A_BOLD);
    printw("%.1f ", memory->swap_total);
    attroff(A_BOLD);
    printw("total,   ");
    attron(A_BOLD);
    printw("%.1f ", memory->swap_free);
    attroff(A_BOLD);
    printw("free,   ");
    attron(A_BOLD);
    printw("%.1f ", memory->swap_used);
    attroff(A_BOLD);
    printw("used,   ");
    attron(A_BOLD);
    printw("%.1f ", memory->available);
    attroff(A_BOLD);
    printw("avail Mem\n\n");
}

void print_memory(void)
{
    memory_stats_t memory;

    get_memory_infos(&memory);
    print_memory_first_part(&memory);
    memory_second_part(&memory);
}
