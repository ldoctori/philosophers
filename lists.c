#include "philosophers.h"

t_philo *philo_list_init(t_input *input)
{
    int i;
    t_philo *philo;
    t_philo *tmp;
    t_philo  *start;

    philo = malloc(sizeof(t_philo));
    philo->input = input;
    philo->number_of_meal = 0;
    philo->philo_id = 1;
    start = philo;
    i = 2;
    while (i <= input->philo_num)
    {
        
        tmp = malloc(sizeof(t_philo));
        philo->next = tmp;
        philo = philo->next;
        philo->input = input;
        philo->number_of_meal = 0;
        philo->philo_id = i;
        i++;
    }
    philo->next = start;
    return (start);
}

t_mutex *mtx_list_init(int number)
{
    int i;
    t_mutex *mtx;
    t_mutex *start;

    mtx = malloc(sizeof(t_mutex));
    pthread_mutex_init(&mtx->mutex, NULL);
    start = mtx;
    i = 1;
    while (i < number)
    {
        mtx->next = malloc(sizeof(t_mutex));
        mtx->next->prev = mtx;
        mtx = mtx->next;
        pthread_mutex_init(&mtx->mutex, NULL);
        i++;
    }
    mtx->next = start;
    start->prev = mtx;
    return (start);

}

void philo_mtx_accordance(t_philo *philo, t_mutex *mtx, struct timeval *tv)
{
    philo->left = &mtx->mutex;
    philo->right = &mtx->prev->mutex;
    philo->time_of_last_meal_sec = tv->tv_sec;
    philo->time_of_last_meal_usec = tv->tv_usec;
    philo->time_of_start_sec = tv->tv_sec;
    philo->time_of_start_usec = tv->tv_usec;
    philo = philo->next;
    mtx = mtx->next;
    while (philo->philo_id != 1)
    {
        philo->left = &mtx->mutex;
        philo->right = &mtx->prev->mutex;
        philo->time_of_last_meal_sec = tv->tv_sec;
        philo->time_of_last_meal_usec = tv->tv_usec;
        philo->time_of_start_sec = tv->tv_sec;
        philo->time_of_start_usec = tv->tv_usec;
        philo = philo->next;
        mtx = mtx->next;
    }
}