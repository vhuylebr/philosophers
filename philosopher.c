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
        pthread_mutex_unlock(&philo->chopstick);
        while (i < nb_philo) {
                philo->tail->next = malloc(sizeof(list_t));
                philo->tail->next->next = NULL;
                philo->tail->next->id = i;
                philo->tail->next->nb_rice = nb_rice;
                philo->tail->next->use_left = 0;
                philo->tail->next->use_right = 0;
                philo->tail->next->chopstick = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
                pthread_mutex_unlock(&philo->tail->next->chopstick);
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

void set_eating(list_t *to_eat)
{
        pthread_mutex_lock(&to_eat->chopstick);
        pthread_mutex_lock(&to_eat->next->chopstick);
        write(1, "zz", 2);
        to_eat->state = EATING;
        --to_eat->nb_rice;
}

void set_resting(list_t *to_rest)
{
        pthread_mutex_unlock(&to_rest->chopstick);
        pthread_mutex_unlock(&to_rest->next->chopstick);
        to_rest->state = RESTING;
}

void set_thinking(list_t *to_think)
{
        if (!pthread_mutex_trylock(&to_think->next->chopstick)) {
                pthread_mutex_lock(&to_think->chopstick);
        } else if (!pthread_mutex_trylock(&to_think->chopstick)) {
                pthread_mutex_lock(&to_think->next->chopstick);
        }
        to_think->state = THINKING;
}

void start(list_t *philo, int nb_philo)
{
        list_t *tmp = philo;
        int end = 0;

        while (tmp->next) {
                if (tmp->state == EATING)
                        set_resting(tmp);
                else if (pthread_mutex_trylock(&tmp->chopstick) == 16) {
                        if (pthread_mutex_trylock(&tmp->next->chopstick) == 16) {
                                tmp->state = RESTING;
                        } else {
                                pthread_mutex_unlock(&tmp->next->chopstick);
                                tmp->state = RESTING;
                        }
                } else if (pthread_mutex_trylock(&tmp->next->chopstick) == 16) {
                        tmp->state = RESTING;
                        pthread_mutex_unlock(&tmp->chopstick);
                } else {
                        tmp->state = EATING;
                        --tmp->nb_rice;
                }
                /*
                } else if (tmp->nb_rice > 0 && tmp->state == THINKING && pthread_mutex_trylock(&tmp->chopstick) == 0 &&
                        pthread_mutex_trylock(&tmp->next->chopstick) == 0) {
                                tmp->state = EATING;
                } else {
                        tmp->state = THINKING;
                }*/
                printf("philo nb=%i is %i and left %i rice and %i philosophers has finish\n", tmp->id, (int)tmp->state, tmp->nb_rice, end);
                if (tmp->nb_rice == 0)
                        ++end;
                if (end >= nb_philo)
                        break;
                if (tmp->id == nb_philo - 1) {
                        //break ;
                        printf("------------------------------------------------------\n");
                        end = 0;
                }
                tmp = tmp->next;
        }
}

int main(int ac, char **av)
{
        list_t *philo = NULL;


        //RCFStartup(ac, av);
	if (ac > 1 && strcmp(av[1], "--help") == 0)
		help();
	if (ac != 5)
		return (84);
	if (atoi(av[2]) <= 0 || atoi(av[4]) < 0)
		return (84);
        philo = init(atoi(av[2]), atoi(av[4]), philo);
        start(philo, atoi(av[2]));
	//RCFCleanup();
        return (0);
}
