/*
** EPITECH PROJECT, 2025
** G-PSU-100-MAR-1-1-mytop-15
** File description:
** isnum.c
*/

#include "../../include/my.h"

bool isnum(char c)
{
    if (c >= '0' && c <= '9')
        return true;
    return false;
}
