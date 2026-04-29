/*
** EPITECH PROJECT, 2026
** G-PSU-100-MAR-1-1-mytop-15
** File description:
** Get users online
*/

#include "../../include/my.h"

static FILE *open_utmp_file(void)
{
    FILE *file;

    file = fopen("/run/utmp", "rb");
    if (file == NULL)
        file = fopen("/var/run/utmp", "rb");
    return file;
}

int count_users(void)
{
    FILE *file;
    struct utmpx user;
    int count = 0;

    file = open_utmp_file();
    if (file == NULL)
        return 0;
    while (fread(&user, sizeof(struct utmpx), 1, file) == 1) {
        if (user.ut_type == USER_PROCESS)
            count++;
    }
    fclose(file);
    return count;
}
