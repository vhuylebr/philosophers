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

void add_philo()
{

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
        while (i < nb_philo) {
                philo->tail->next = malloc(sizeof(list_t));
                philo->tail->next->next = NULL;
                philo->tail->next->id = i;
                philo->tail->next->nb_rice = nb_rice;
                philo->tail->next->use_left = 0;
                philo->tail->next->use_right = 0;
                philo->tail->next->state = UNDIFINED;
                philo->tail->next->prev = philo->tail;
                philo->tail = philo->tail->next;
                ++i;
        }
        philo->tail->next = philo->head;
        philo->head->prev = philo->tail;
        return philo;
}

void set_eating(list_t *to_eat)
{
        to_eat->use_left = 1;
        to_eat->use_right = 1;
        to_eat->state = EATING;
        --to_eat->nb_rice;
}

void set_resting(list_t *to_rest)
{
        to_rest->use_left = 0;
        to_rest->use_right = 0;
        to_rest->state = RESTING;
}

void set_thinking(list_t *to_think)
{
        if (!to_think->prev->use_right) {
                to_think->use_left = 1;
                to_think->use_right = 0;
        }
        else if (!to_think->next->use_left) {
                to_think->use_right = 1;
                to_think->use_left = 0;
        }
        to_think->state = THINKING;
}

void start(list_t *philo, int nb_philo)
{
        list_t *tmp = philo;
        int end = 0;

        while (tmp->next) {
                if (tmp->state != EATING && !tmp->prev->use_right &&
                        !tmp->next->use_left && tmp->nb_rice > 0)
                        set_eating(tmp);
                else if (tmp->state == EATING) {
                        set_resting(tmp);
                } else if (tmp->state != THINKING && (!tmp->prev->use_right ||
                        !tmp->prev->use_left)) {
                        set_thinking(tmp);
                }
                printf("philo nb=%i is %i and left %i rice and %i philosophers has finish\n", tmp->id, (int)tmp->state, tmp->nb_rice, end);
                if (tmp->nb_rice == 0)
                        ++end;
                if (end >= nb_philo)
                        break;
                if (tmp->id == nb_philo - 1) {
                        printf("------------------------------------------------------\n");
                        end = 0;
                }
                tmp = tmp->next;
        }
}

int main(int ac, char **av)
{
        list_t *philo = NULL;

	if (ac > 1 && strcmp(av[1], "--help") == 0)
		help();
	if (ac != 5)
		return (84);
	if (atoi(av[2]) <= 0 || atoi(av[4]) < 0)
		return (84);
        philo = init(atoi(av[2]), atoi(av[4]), philo);
        start(philo, atoi(av[2]));
        return (0);
}
