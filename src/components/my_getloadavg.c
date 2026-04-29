/*
** EPITECH PROJECT, 2026
** G-PSU-100-MAR-1-1-mytop-15
** File description:
** Get system load averages
*/

#include "../../include/my.h"

static int check_nelem(int nelem)
{
    if (nelem > 3)
        nelem = 3;
    return nelem;
}

static void error_handling(FILE *fp, char *buffer)
{
    fp = fopen("/proc/loadavg", "r");
    if (fp == NULL)
        exit(ERROR_RETURN);
    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
        fclose(fp);
        exit(ERROR_RETURN);
    }
    fclose(fp);
}

int my_getloadavg(double loadavg[], int nelem, int i)
{
    FILE *fp;
    int original_nelem = nelem;
    char *token;
    char buffer[128];

    nelem = check_nelem(nelem);
    error_handling(fp, buffer);
    fp = fopen("/proc/loadavg", "r");
    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);
    token = strtok(buffer, " ");
    while (token != NULL && i < nelem) {
        loadavg[i] = atof(token);
        i++;
        token = strtok(NULL, " ");
    }
    if (original_nelem > 3)
        for (; i < original_nelem; i++)
            loadavg[i] = 0.0;
    return i;
}
