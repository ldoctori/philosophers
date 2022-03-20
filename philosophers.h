#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_input
{
    int      philo_num;
    long    time_to_die;
    long    time_to_eat;
    long     time_to_sleep;
    int      max_number_of_meal;
}   t_input;

typedef struct s_mutex
{
    pthread_mutex_t mutex;
    struct s_mutex *next;
    struct s_mutex *prev;
} t_mutex;

typedef struct s_philo
{
    struct s_philo *next;

    t_mutex         *left;
    t_mutex         *right;
    pthread_mutex_t *dead;
    long        time_of_last_meal;
    long        time_of_start_sec;
    long        time_of_start_usec;
    int             philo_id;
    int             number_of_meal;
    int             eat_state;
    struct timeval  tv;
    t_input         *input;
}   t_philo;

int         ft_atoi(const char *str);
t_philo     *philo_list_init(t_input *input);
t_mutex     *mtx_list_init(int number);
void        philo_mtx_accordance(t_philo *philo, t_mutex *mtx, struct timeval *tv, pthread_mutex_t *dead);
void        take_input(t_input *input, char **argv);
pthread_t   **arr_create(int philo_num);
int         die_check(t_philo *philo);
int         get_time(t_philo *philo);

void        free_philo(t_philo *philo);
void        free_destroy_mtx(t_mutex *mtx, int num);
void        free_thread_arr(pthread_t **arr, int num);

#endif