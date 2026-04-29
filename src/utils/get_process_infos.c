/*
** EPITECH PROJECT, 2025
** G-PSU-100-MAR-1-1-mytop-15
** File description:
** get_process_infos.c
*/

#include "../../include/my.h"
#include <pwd.h>
#include <sys/sysinfo.h>

static void parse_value(process_stats_t *process, stat_parse_t *data)
{
    long page_size = sysconf(_SC_PAGESIZE);

    process->state = data->state;
    process->priority = (int)data->priority;
    process->nice = (int)data->nice;
    process->virt = data->vsize / 1024;
    process->utime = data->utime;
    process->stime = data->stime;
    process->res = (data->rss * page_size) / 1024;
}

static void read_value(process_stats_t *proc, FILE *fd, stat_parse_t *d)
{
    char comm[256];
    char state;
    int ppid;
    int pgrp;
    int session;
    int tty_nr;
    int tpgid;
    unsigned long flags;
    unsigned long minflt;
    unsigned long cminflt;
    unsigned long majflt;

    fscanf(fd, "%d %s %c %d %d %d %d %d %lu %lu %lu %lu %lu",
        &proc->pid, comm, &state, &ppid, &pgrp, &session, &tty_nr, &tpgid,
        &flags, &minflt, &cminflt, &majflt, &d->cmajflt);
    fscanf(fd, "%lu %lu %ld %ld %ld %ld %ld %ld %lu %lu %ld",
        &d->utime, &d->stime, &d->cutime, &d->cstime, &d->priority, &d->nice,
        &d->num_threads, &d->itrealvalue, &d->starttime, &d->vsize, &d->rss);
    d->state = state;
}

static int get_uid_from_status(const char *filepath_status)
{
    FILE *fd = fopen(filepath_status, "r");
    char line[256];
    int uid = -1;

    if (fd == NULL)
        return -1;
    while (fgets(line, sizeof(line), fd)) {
        if (strncmp(line, "Uid:", 4) == 0) {
            sscanf(line, "Uid:\t%d", &uid);
            break;
        }
    }
    fclose(fd);
    return uid;
}

static void parse_stat_file(process_stats_t *process, const char *filepath)
{
    FILE *fd = fopen(filepath, "r");
    stat_parse_t data;

    if (fd == NULL)
        return;
    data.state = ' ';
    read_value(process, fd, &data);
    parse_value(process, &data);
    fclose(fd);
}

static void parse_statm_file(process_stats_t *process, const char *filepath)
{
    FILE *fd = fopen(filepath, "r");
    unsigned long size;
    unsigned long resident;
    unsigned long shared;
    long page_size;

    if (fd == NULL)
        return;
    fscanf(fd, "%lu %lu %lu", &size, &resident, &shared);
    fclose(fd);
    page_size = sysconf(_SC_PAGESIZE);
    process->shr = (shared * page_size) / 1024;
}

static void get_mem_percentage(process_stats_t *process)
{
    FILE *fd = fopen("/proc/meminfo", "r");
    char line[256];
    unsigned long mem_total = 0;

    if (fd == NULL)
        return;
    while (fgets(line, sizeof(line), fd)) {
        if (strncmp(line, "MemTotal:", 9) == 0) {
            sscanf(line, "MemTotal: %lu kB", &mem_total);
            break;
        }
    }
    fclose(fd);
    if (mem_total > 0)
        process->mem_usage = (100.0 * process->res) / mem_total;
}

static void get_command(process_stats_t *process, int pid)
{
    read_comm_file(process, pid);
    if (process->command[0] == '\0')
        read_cmdline_file(process, pid);
}

void get_process_infos(process_stats_t *process, process_paths_t *paths)
{
    int uid = get_uid_from_status(paths->status);

    if (uid != -1)
        get_user_from_uid(uid, process->user);
    parse_stat_file(process, paths->stat);
    parse_statm_file(process, paths->statm);
    get_mem_percentage(process);
    get_command(process, paths->pid);
    format_process_time(process);
}
