/*
** EPITECH PROJECT, 2025
** G-PSU-100-MAR-1-1-mytop-15
** File description:
** buffer_to_userlist.c
*/

#include "../../include/my.h"

static int count_line(char *buffer)
{
    int line = 0;
    int i = 0;

    for (i = 0; buffer[i] != '\0'; i++){
        if (buffer[i] == '\n')
            line++;
    }
    return line;
}

static int linebreak(char *buffer, int i)
{
    while (buffer[i] != '\n')
        i++;
    i++;
    return i;
}

static int charnb(char *buffer, int i, int count)
{
    while (buffer[i] != ':'){
        count++;
        i++;
    }
    count++;
    return count;
}

char **buffer_to_userlist(char *buffer)
{
    int line_nb = count_line(buffer);
    char **tab = malloc(sizeof(char *) * (line_nb + 1));
    int i = 0;
    int z = 0;
    int count = 0;

    for (int j = 0; j != line_nb; j++){
        if (j != 0)
            i = linebreak(buffer, i);
        count = charnb(buffer, i, count);
        tab[j] = malloc(sizeof(char) * count + 1);
        for (; buffer[i] != ':'; i++){
            tab[j][z] = buffer[i];
            z++;
        }
        z = 0;
        tab[j][count] = '\0';
    }
    tab[line_nb] = NULL;
    return tab;
}
