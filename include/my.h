/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** Library
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <utmpx.h>
#include <dirent.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/sysinfo.h>

#ifndef MY_H_
    #define MY_H_

    #define ERROR_RETURN 84
    #define MAX_PROCESSES 512

typedef struct options_s {

    bool U_flag;
    bool d_flag;
    bool n_flag;
    char *username;
    float delay;
    int frames;

} options_t;

typedef struct uptime_s {
    int hour;
    int minutes;
    int days;
} uptime_t;

typedef struct coma_s {
    int before_coma;
    float after_coma;
} coma_t;

typedef struct task_stats_s {
    int total;
    int running;
    int sleeping;
    int stopped;
    int zombie;
} task_stats_t;

typedef struct memory_stats_st {
    float total;
    float free;
    float used;
    float swap_total;
    float swap_free;
    float swap_used;
    float available;
    float buffers;
    float cached;
    float sreclaimable;
} memory_stats_t;

typedef struct cpu_stats_s {
    float us;
    float sy;
    float ni;
    float id;
    float wa;
    float hi;
    float si;
    float st;
} cpu_stats_t;

typedef struct process_paths_s {
    char status[128];
    char stat[128];
    char statm[128];
    int pid;
} process_paths_t;

typedef struct stat_parse_s {
    char state;
    unsigned long cmajflt;
    unsigned long utime;
    unsigned long stime;
    long cutime;
    long cstime;
    long priority;
    long nice;
    long num_threads;
    long itrealvalue;
    unsigned long starttime;
    unsigned long vsize;
    long rss;
} stat_parse_t;

typedef struct process_stats_s {
    int pid;
    char user[32];
    int priority;
    int nice;
    char state;
    unsigned long virt;
    unsigned long res;
    unsigned long shr;
    double cpu_usage;
    double mem_usage;
    unsigned long utime;
    unsigned long stime;
    unsigned long last_utime;
    unsigned long last_stime;
    unsigned long last_time;
    char time[16];
    char command[256];
} process_stats_t;

typedef struct process_manager_s {
    process_stats_t processes[512];
    int count;
    unsigned long last_uptime;
} process_manager_t;


int my_getloadavg(double loadavg[], int nelem, int i);
void get_task_stats(task_stats_t *stats);
void options_parsing(int ac, char **av, options_t *options);
bool check_user_isvalid(char *user);
char **buffer_to_userlist(char *buffer);
void print_terminal(options_t *options, int temp, int check_interval);
void print_header(void);
void print_uptime(int full_days, coma_t *float_division);
int count_users(void);
void print_memory(void);
void get_cpu_stats(cpu_stats_t *stats);
bool isnum(char c);
void print_process(process_manager_t *mgr);
void get_process_infos(process_stats_t *process, process_paths_t *paths);
void get_user_from_uid(int uid, char *user_out);
void read_comm_file(process_stats_t *process, int pid);
void read_cmdline_file(process_stats_t *process, int pid);
void format_process_time(process_stats_t *process);

#endif
