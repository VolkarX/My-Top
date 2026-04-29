/*
** EPITECH PROJECT, 2025
** G-PSU-100-MAR-1-1-mytop-15
** File description:
** options_parsing.c
*/

#include "../../include/my.h"

static void check_n_flag(options_t *options, char **av, int i)
{
    if (!av[i + 1])
        exit(ERROR_RETURN);
    if (atoi(av[i + 1]) == 0)
        exit(ERROR_RETURN);
    options->n_flag = true;
    options->frames = atoi(av[i + 1]);
}

static void check_d_flag(options_t *options, char **av, int i)
{
    if (!av[i + 1])
        exit(ERROR_RETURN);
    if (atof(av[i + 1]) == 0)
        exit(ERROR_RETURN);
    options->d_flag = true;
    options->delay = atof(av[i + 1]);
}

static void check_u_flag(options_t *options, char **av, int i)
{
    if (!av[i + 1])
        exit(ERROR_RETURN);
    if (check_user_isvalid(av[i + 1]) == false)
        exit(ERROR_RETURN);
    options->U_flag = true;
    options->username = strdup(av[i + 1]);
}

static void check_flags(int i, char **av, options_t *options)
{
    if (av[i][1] != 'U' && av[i][1] != 'd' && av[i][1] != 'n')
        exit(ERROR_RETURN);
    if (av[i][1] == 'n')
        check_n_flag(options, av, i);
    if (av[i][1] == 'd')
        check_d_flag(options, av, i);
    if (av[i][1] == 'U')
        check_u_flag(options, av, i);
}

void options_parsing(int ac, char **av, options_t *options)
{
    for (int i = 0; i < ac; i++)
        if (av[i][0] == '-')
            check_flags(i, av, options);
}
