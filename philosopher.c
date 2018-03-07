/*
** EPITECH PROJECT, 2018
** philo
** File description:
** philo
*/

#include "philosopher.h"

void help(void)
{
	printf("USAGE\n\t./philo -p nbr_p -e nbr_e\n\nDESCRIPTION\n\t");
	printf("-p nbr_p number of philosophers\n\t");
	printf("-e nbr_e maximum number times a philosopher ");
	printf("eats before exiting the program\n");
}

void init_philo(list_t *philo, int nb_rice, int i)
{
	philo->tail->next = malloc(sizeof(list_t));
	philo->tail->next->next = NULL;
	philo->tail->next->id = i;
	philo->tail->next->nb_rice = nb_rice;
	philo->tail->next->chopstick = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	philo->tail->next->state = UNDIFINED;
	philo->tail = philo->tail->next;
}

list_t *init(int nb_philo, int nb_rice, list_t *philo)
{
	philo = malloc(sizeof(list_t));
	int i = 1;

	philo->next = NULL;
	philo->tail = philo;
	philo->head = philo;
	philo->id = 0;
	philo->nb_rice = nb_rice;
	philo->state = UNDIFINED;
	philo->chopstick = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	while (i < nb_philo) {
		init_philo(philo, nb_rice, i);
		++i;
	}
	philo->tail->next = philo->head;
	return (philo);
}

void eat_rest(list_t *tmp)
{
	tmp->state = EATING;
	pthread_mutex_lock(&tmp->chopstick);
	lphilo_take_chopstick(&tmp->chopstick);
	lphilo_take_chopstick(&tmp->next->chopstick);
	lphilo_eat();
	lphilo_release_chopstick(&tmp->chopstick);
	lphilo_release_chopstick(&tmp->next->chopstick);
	pthread_mutex_unlock(&tmp->next->chopstick);
	pthread_mutex_unlock(&tmp->chopstick);
	--tmp->nb_rice;
	tmp->state = RESTING;
	lphilo_sleep();
}

void *start(void *philo)
{
	list_t *tmp = philo;

	while (tmp->nb_rice > 0) {
		if (pthread_mutex_trylock(&tmp->chopstick) == 0) {
			tmp->state = THINKING;
			lphilo_take_chopstick(&tmp->chopstick);
			lphilo_think();
			pthread_mutex_unlock(&tmp->chopstick);
			lphilo_release_chopstick(&tmp->chopstick);
			if (pthread_mutex_trylock(&tmp->next->chopstick) == 0) {
				eat_rest(tmp);
			} else
				pthread_mutex_unlock(&tmp->chopstick);
		}
	}
	return (tmp);
}
