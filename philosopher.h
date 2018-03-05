/*
** EPITECH PROJECT, 2018
** philosopher.h
** File description:
** header
*/

#ifndef PHILOSOPHER_H_
# define PHILOSOPHER_H_

# define NB_TRAINS 3

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

typedef enum State {
        RESTING,
        THINKING,
        EATING,
        UNDIFINED
} State;

typedef struct list_s {
        int id;
        State state;
        int use_left;
        pthread_mutex_t chopstick;
	pthread_t thread;
        int use_right;
        int nb_rice;
        struct list_s *tail;
        struct list_s *head;
        struct list_s *prev;
        struct list_s *next;
}               list_t;
#endif /* !PHILOSOPHER_H_ */
