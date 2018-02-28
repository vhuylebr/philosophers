/*
** EPITECH PROJECT, 2018
** philosopher.c
** File description:
** function
*/

#include "philosopher.h"

# define NB_TRAINS 3
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


void *train()
{
	char track[] = "=====|====|=====";
	// char track1[] = "=====|====|=====";
	// char track2[] = "=====|====|=====";
	char tmp;
	static int t = 0;
	int i = 0;

	while (track[i - 1] != '|') {
		pthread_mutex_lock(&mutex);
		if (track[i - 1] == '#')
			track[i - 1] = '=';
		if (track[i] == '|') {
			track[i++];
			while (t == 1) {
				pthread_cond_wait(&cond, &mutex);
			}
			t++;
			pthread_mutex_unlock(&mutex);
		} else {
			tmp = '#';
			track[i++] = tmp;
			usleep(50000);
			printf("%s\n", track);
		}
	}
	while (track[i]) {

		if (track[i - 1] == '#')
			track[i - 1] = '=';
		if (track[i] == '|') {
			pthread_mutex_lock(&mutex);
			--t;
			pthread_cond_signal(&cond);
			pthread_mutex_unlock(&mutex);
		}
		else {
			tmp = '#';
			track[i++] = tmp;
			usleep(50000);
			printf("%s\n", track);
		}
	}
}

int main()
{
	pthread_t     train1;
        pthread_t     train2;
        pthread_t     train3;

        pthread_create(&train1, NULL, train, NULL);
        pthread_create(&train2, NULL, train, NULL);
        pthread_create(&train3, NULL, train, NULL);

        pthread_join(train1, NULL);
        pthread_join(train2, NULL);
        pthread_join(train3, NULL);
}
//
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
//
// void    *train()
// {
//     int   km;
//     static int t = 0;
//
//     km = 1;
//     while (km != 30)
//     {
//         printf("%02dkm\n", km);
//
//         // If we've reached the bridge, wait until less than two trains are on it.
//         if (km == 2)
//         {
//             pthread_mutex_lock(&mutex);
//             while (t == 1) { // To be read as: "While two trains are on the bridge, wait."
//                 pthread_cond_wait(&cond, &mutex);
//             }
//             ++t; // Put this train onto the bridge.
//             pthread_mutex_unlock(&mutex);
//         }
//		if (km == 3)
// 		printf("you're on the bridge\n");
//         // Leave the bridge.
//         if (km == 4)
//         {
//             pthread_mutex_lock(&mutex);
//             --t; // Take this train off the bridge.
//             pthread_cond_signal(&cond); // Signal another train to enter.
//             pthread_mutex_unlock(&mutex);
//         }
//
//         // Move forward 1 km.
//         sleep(1);
//         ++km;
//     }
// }
//
// int     main()
// {
//     pthread_t     train1;
//     pthread_t     train2;
//     pthread_t     train3;
//     pthread_t     train4;
//
//     pthread_create(&train1, NULL, train, NULL);
//     pthread_create(&train2, NULL, train, NULL);
//     pthread_create(&train3, NULL, train, NULL);
//     pthread_create(&train4, NULL, train, NULL);
//
//     pthread_join(train1, NULL);
//     pthread_join(train2, NULL);
//     pthread_join(train3, NULL);
//     pthread_join(train4, NULL);
// }
