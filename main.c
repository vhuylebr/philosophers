/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** function
*/

#include "philosopher.h"

void check_help(char **av, arg_t *arg)
{
	if (strcmp(av[1], "-p") == 0 && strcmp(av[3], "-e") == 0) {
		arg->nb_rice = atoi(av[4]);
		arg->nb_philo = atoi(av[2]);
	} else if (strcmp(av[1], "-e") == 0 && strcmp(av[3], "-p") == 0) {
		arg->nb_rice = atoi(av[2]);
		arg->nb_philo = atoi(av[4]);
	} else
		exit(84);
}

void check_arg(int ac, char **av, arg_t *arg)
{
	if (ac > 1 && strcmp(av[1], "--help") == 0) {
		help();
		exit(0);
	} else if (ac != 5)
		exit(84);
	check_help(av, arg);
	if (arg->nb_philo <= 1 || arg->nb_rice < 0)
		exit(84);
}

int main(int ac, char **av)
{
	list_t *philo = NULL;
	list_t *tmp;
	arg_t arg;

	check_arg(ac, av, &arg);
	RCFStartup(ac, av);
	philo = init(arg.nb_philo, arg.nb_rice, philo);
	tmp = philo;
	for (int i = 0; i < arg.nb_philo; ++i) {
		pthread_create(&tmp->thread, NULL, &start, (void *)tmp);
		tmp = tmp->next;
		usleep(5000);
	}
	tmp = philo;
	for (int i = 0; i < arg.nb_philo; ++i) {
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
	}
	RCFCleanup();
	return (0);
}
