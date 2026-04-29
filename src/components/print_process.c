/*
** EPITECH PROJECT, 2025
** G-PSU-100-MAR-1-1-mytop-15
** File description:
** print_process.c
*/

#include "../../include/my.h"

static char *get_path(char *specifier, char pid[])
{
    char *filepath = malloc(sizeof(char) * 128);

    strcpy(filepath, "/proc/");
    strcat(filepath, pid);
    strcat(filepath, specifier);
    return filepath;
}

static unsigned long get_system_uptime(void)
{
    struct sysinfo si;

    if (sysinfo(&si) == 0)
        return si.uptime;
    return 0;
}

static void calc_cpu(process_stats_t *p, unsigned long hz,
    unsigned long up, unsigned long last_up)
{
    unsigned long delta_utime;
    unsigned long delta_stime;
    unsigned long delta_uptime;

    if (p->last_time > 0 && last_up > 0) {
        delta_utime = p->utime - p->last_utime;
        delta_stime = p->stime - p->last_stime;
        delta_uptime = up - last_up;
        if (delta_uptime > 0)
            p->cpu_usage = 100.0 * (delta_utime + delta_stime) /
                (delta_uptime * hz);
    }
    p->last_utime = p->utime;
    p->last_stime = p->stime;
    p->last_time = up;
}

static void calculate_cpu_percentage(process_stats_t *process,
    process_manager_t *mgr)
{
    long hz = sysconf(_SC_CLK_TCK);
    unsigned long current_uptime = get_system_uptime();

    calc_cpu(process, hz, current_uptime, mgr->last_uptime);
}

static void print_process_line(process_stats_t *process)
{
    printw("%7d %-8s %3d %3d %c %7lu %7lu %7lu %5.1f %5.1f %9s",
        process->pid, process->user, process->priority, process->nice,
        process->state, process->virt, process->res, process->shr,
        process->cpu_usage, process->mem_usage, process->time);
    printw(" %s\n", process->command);
}

static void collect_info(char pid[], process_manager_t *mgr)
{
    char *filepath_stat = get_path("/stat", pid);
    char *filepath_status = get_path("/status", pid);
    char *filepath_statm = get_path("/statm", pid);
    process_stats_t *process = &mgr->processes[mgr->count];
    process_paths_t paths;

    if (mgr->count >= MAX_PROCESSES)
        return;
    memset(process, 0, sizeof(process_stats_t));
    strcpy(paths.status, filepath_status);
    strcpy(paths.stat, filepath_stat);
    strcpy(paths.statm, filepath_statm);
    paths.pid = atoi(pid);
    get_process_infos(process, &paths);
    calculate_cpu_percentage(process, mgr);
    free(filepath_status);
    free(filepath_stat);
    free(filepath_statm);
}

static void list_pid_folders(process_manager_t *mgr)
{
    DIR *proc_dir = opendir("/proc");
    struct dirent *directory;

    if (proc_dir == NULL) {
        perror("opendir");
        return;
    }
    mgr->count = 0;
    directory = readdir(proc_dir);
    while (directory != NULL) {
        if (isdigit(directory->d_name[0])) {
            collect_info(directory->d_name, mgr);
            mgr->count++;
        }
        directory = readdir(proc_dir);
    }
    closedir(proc_dir);
}

void print_process(process_manager_t *mgr)
{
    int i;

    list_pid_folders(mgr);
    mgr->last_uptime = get_system_uptime();
    printw("    PID USER     PR  NI S    VIRT    RES    SHR");
    printw(" %%CPU %%MEM      TIME+ COMMAND\n");
    i = 0;
    while (i < mgr->count) {
        print_process_line(&mgr->processes[i]);
        i++;
    }
}
