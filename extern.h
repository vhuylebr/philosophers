/*
** EPITECH PROJECT, 2018
** header
** File description:
** header
*/

#ifndef __LIBRICEFEREE_EXTERN__
# define __LIBRICEFEREE_EXTERN__

#include <pthread.h>

int	RCFStartup(int ac, char **av);
void	RCFCleanup(void);
int	lphilo_eat(void);
int	lphilo_sleep(void);
int	lphilo_think(void);
int	lphilo_take_chopstick(const pthread_mutex_t *mutex_id);
int	lphilo_release_chopstick(const pthread_mutex_t *mutex_id);

#endif /* __LIBRICEFEREE_EXTERN__ */
