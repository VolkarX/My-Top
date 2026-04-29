/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** Main file
*/

#include "../include/my.h"

static void init_options(options_t *options)
{
    options->d_flag = false;
    options->U_flag = false;
    options->n_flag = false;
    options->delay = 3.0;
    options->frames = 2147483647;
}

int main(int argc, char **argv)
{
    options_t *options = malloc(sizeof(options_t));

    init_options(options);
    options_parsing(argc, argv, options);
    print_terminal(options, 0, 50);
    free(options);
    return 0;
}
