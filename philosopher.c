/*
** EPITECH PROJECT, 2018
** philo
** File description:
** philo
*/

#include "extern.h"
#include "philosopher.h"

void help()
{
	printf("USAGE\n\t./philo -p nbr_p -e nbr_e\n\nDESCRIPTION\n\t");
	printf("-p nbr_p number of philosophers\n\t");
	printf("-e nbr_e maximum number times a philosopher ");
	printf("eats before exiting the program\n");
}

list_t *init(int nb_philo, int nb_rice, list_t *philo)
{
        philo = malloc(sizeof(list_t));
        int i = 1;

        philo->next = NULL;
        philo->prev = NULL;
        philo->tail = philo;
        philo->head = philo;
        philo->id = 0;
        philo->nb_rice = nb_rice;
        philo->use_left = 0;
        philo->use_right = 0;
        philo->state = UNDIFINED;
        philo->chopstick = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
        while (i < nb_philo) {
                philo->tail->next = malloc(sizeof(list_t));
                philo->tail->next->next = NULL;
                philo->tail->next->id = i;
                philo->tail->next->nb_rice = nb_rice;
                philo->tail->next->use_left = 0;
                philo->tail->next->use_right = 0;
                philo->tail->next->chopstick = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
                philo->tail->next->state = UNDIFINED;
                philo->tail->next->prev = philo->tail;
                philo->tail = philo->tail->next;
                ++i;
        }
        philo->tail->next = philo->head;
        philo->head->prev = philo->tail;
        //pthread_mutex_lock(&philo->chopstick);
        //printf("%i\n", pthread_mutex_trylock(&philo->chopstick));
        //exit(0);
        return philo;
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
                	} else
				pthread_mutex_unlock(&tmp->chopstick);
        	}
	}
	return (tmp);
}

int main(int ac, char **av)
{
        list_t *philo = NULL;
	list_t *tmp;
	int i;

        RCFStartup(ac, av);
	if (ac > 1 && strcmp(av[1], "--help") == 0)
		help();
	if (ac != 5)
		return (84);
	if (atoi(av[2]) <= 0 || atoi(av[4]) < 0)
		return (84);
        philo = init(atoi(av[2]), atoi(av[4]), philo);
	tmp = philo;
	for (i = 0; i < atoi(av[2]); ++i) {
		pthread_create(&tmp->thread, NULL, &start, (void *)tmp);
		tmp = tmp->next;
		usleep(20000);
	}
	tmp = philo;
	for (i = 0; i < atoi(av[2]); ++i) {
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
	}
        // start(philo, atoi(av[2]));
	RCFCleanup();
        return (0);
}
