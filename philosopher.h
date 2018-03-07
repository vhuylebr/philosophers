/*
** EPITECH PROJECT, 2018
** philosopher.h
** File description:
** header
*/

#ifndef PHILOSOPHER_H_
# define PHILOSOPHER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include "extern.h"

typedef enum State {
        RESTING,
        THINKING,
        EATING,
        UNDIFINED
} State;

typedef struct list_s {
        int id;
        State state;
        pthread_mutex_t chopstick;
	pthread_t thread;
        int nb_rice;
        struct list_s *tail;
        struct list_s *head;
        struct list_s *next;
}               list_t;

typedef struct arg_s {
	int nb_philo;
	int nb_rice;
}		arg_t;

void help(void);
list_t *init(int nb_philo, int nb_rice, list_t *philo);
void *start(void *philo);

#endif /* !PHILOSOPHER_H_ */
