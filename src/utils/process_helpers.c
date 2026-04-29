/*
** EPITECH PROJECT, 2025
** G-PSU-100-MAR-1-1-mytop-15
** File description:
** process_helpers.c
*/

#include "../../include/my.h"
#include <pwd.h>

void get_user_from_uid(int uid, char *user_out)
{
    struct passwd *pw = getpwuid(uid);

    if (pw != NULL) {
        strncpy(user_out, pw->pw_name, 31);
        user_out[31] = '\0';
    } else {
        snprintf(user_out, 32, "%d", uid);
    }
}

void read_comm_file(process_stats_t *process, int pid)
{
    char filepath[128];
    FILE *fd;
    size_t len;

    snprintf(filepath, sizeof(filepath), "/proc/%d/comm", pid);
    fd = fopen(filepath, "r");
    if (fd == NULL)
        return;
    if (fgets(process->command, sizeof(process->command), fd)) {
        len = strlen(process->command);
        if (len > 0 && process->command[len - 1] == '\n')
            process->command[len - 1] = '\0';
    }
    fclose(fd);
}

void read_cmdline_file(process_stats_t *process, int pid)
{
    char filepath[128];
    FILE *fd;

    snprintf(filepath, sizeof(filepath), "/proc/%d/cmdline", pid);
    fd = fopen(filepath, "r");
    if (fd != NULL) {
        fgets(process->command, sizeof(process->command), fd);
        fclose(fd);
    }
}

void format_process_time(process_stats_t *process)
{
    long hz = sysconf(_SC_CLK_TCK);
    unsigned long total_time = process->utime + process->stime;
    unsigned long seconds = total_time / hz;
    unsigned long minutes = seconds / 60;
    unsigned long hours = minutes / 60;

    snprintf(process->time, sizeof(process->time), "%02lu:%02lu:%02lu",
        hours, minutes % 60, seconds % 60);
}
