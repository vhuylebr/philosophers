/*
** EPITECH PROJECT, 2018
** philo
** File description:
** philo
*/

#include "extern.h"
#include "philosopher.h"
#include "string.h"

void help()
{
	printf("USAGE\n\t./philo -p nbr_p -e nbr_e\n\nDESCRIPTION\n\t");
	printf("-p nbr_p number of philosophers\n\t");
	printf("-e nbr_e maximum number times a philosopher ");
	printf("eats before exiting the program\n");
}

int main(int ac, char **av)
{
	if (strcmp(av[1], "--help") == 0)
		help();
	if (ac != 5)
		return (84);
	if (atoi(av[2]) <= 0)
		return (84);
        return (0);
}
