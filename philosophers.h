#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_philo
{
    struct s_philo *next;

    pthread_mutex_t *left;
    pthread_mutex_t *right;
    int             time_to_eat;
    int             time_to_sleep;
    int             time_to_die;
    long int        time_of_last_meal;
    int             philo_id;
    struct timeval tv;
}   t_philo;

typedef struct s_mutex
{
    pthread_mutex_t mutex;
    struct s_mutex *next;
    struct s_mutex *prev;
} t_mutex;

#endif