/*
** EPITECH PROJECT, 2025
** G-PSU-100-MAR-1-1-mytop-15
** File description:
** parse_value.c
*/

#include "../../include/my.h"

float parse_value(char *buffer, char *key)
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

