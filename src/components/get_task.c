/*
** EPITECH PROJECT, 2026
** G-PSU-100-MAR-1-1-mytop-15
** File description:
** Get task information
*/

#include "../../include/my.h"

static int is_pid(const char *name)
{
    int i = 0;

    while (name[i] != '\0') {
        if (!isdigit(name[i]))
            return 0;
        i++;
    }
    return 1;
}

static char parse_state_from_buffer(char *buffer)
{
    char *token;
    char state = '?';

    token = strtok(buffer, ")");
    if (token == NULL)
        return '?';
    token = strtok(NULL, " ");
    if (token != NULL)
        state = token[0];
    return state;
}

static char get_process_state(const char *pid)
{
    char path[256];
    char buffer[512];
    FILE *file;
    char state;

    snprintf(path, sizeof(path), "/proc/%s/stat", pid);
    file = fopen(path, "r");
    if (file == NULL)
        return '?';
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        fclose(file);
        return '?';
    }
    state = parse_state_from_buffer(buffer);
    fclose(file);
    return state;
}

static void count_state(char state, task_stats_t *stats)
{
    if (state == 'R') {
        stats->running++;
        return;
    }
    if (state == 'S' || state == 'D' || state == 'I') {
        stats->sleeping++;
        return;
    }
    if (state == 'Z') {
        stats->zombie++;
        return;
    }
    if (state == 'T' || state == 't')
        stats->stopped++;
}

static void init_stats(task_stats_t *stats)
{
    stats->total = 0;
    stats->running = 0;
    stats->sleeping = 0;
    stats->stopped = 0;
    stats->zombie = 0;
}

static void process_entry(struct dirent *ent, task_stats_t *stats)
{
    char state;

    if (!is_pid(ent->d_name))
        return;
    state = get_process_state(ent->d_name);
    if (state == '?')
        return;
    stats->total++;
    count_state(state, stats);
}

void get_task_stats(task_stats_t *stats)
{
    DIR *directory;
    struct dirent *ent;

    init_stats(stats);
    directory = opendir("/proc");
    if (directory == NULL)
        return;
    ent = readdir(directory);
    while (ent != NULL) {
        process_entry(ent, stats);
        ent = readdir(directory);
    }
    closedir(directory);
}
