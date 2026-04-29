/*
** EPITECH PROJECT, 2025
** G-PSU-100-MAR-1-1-mytop-15
** File description:
** check_user_isvalid.c
*/

#include "../../include/my.h"

static void free_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

static void free_and_close_all(char *buffer, char **userlist, int fd)
{
    free_array(userlist);
    free(buffer);
    close(fd);
}

bool check_user_isvalid(char *user)
{
    struct stat stats;
    int fd;
    char *buffer;
    int size = 0;
    char **userlist;
    bool result = false;

    stat("/etc/passwd", &stats);
    size = stats.st_size;
    buffer = malloc(sizeof(char) * (size + 1));
    fd = open("/etc/passwd", O_RDONLY);
    read(fd, buffer, size);
    userlist = buffer_to_userlist(buffer);
    for (int i = 0; userlist[i] != NULL; i++)
        if (strcmp(user, userlist[i]) == 0)
            result = true;
    free_and_close_all(buffer, userlist, fd);
    if (result == true)
        return true;
    return false;
}
