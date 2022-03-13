#include "philosophers.h"

int die_check(t_philo *philo)
{
    gettimeofday(&philo->tv, NULL);
    if (philo->tv.tv_sec - philo->time_of_last_meal >= philo->time_to_die / 1000000)
        return (1);
    return (0);
}

void *print(void *ph)
{
    t_philo *philo = ph;
    pthread_mutex_lock(philo->right);
    if (die_check(philo) == 1)
    {
        pthread_mutex_unlock(philo->right);
        printf("philosopher %i died\n", philo->philo_id);
        return (NULL);
    }
    printf("philosopher %i has taken right fork\n", philo->philo_id);
    pthread_mutex_lock(philo->left);
    if (die_check(philo) == 1)
    {
        pthread_mutex_unlock(philo->right);
        pthread_mutex_unlock(philo->left);
        printf("philosopher %i died\n", philo->philo_id);
        return (NULL);
    }
    printf("philosopher %i has taken left fork\n", philo->philo_id);
    
    printf("philosopher %i is eating\n", philo->philo_id);
    usleep(philo->time_to_eat);
    pthread_mutex_unlock(philo->right);
    pthread_mutex_unlock(philo->left);

    gettimeofday(&philo->tv, NULL);
    philo->time_of_last_meal = philo->tv.tv_sec;
    printf("philosopher %i is sleeping\n", philo->philo_id);
    usleep(philo->time_to_sleep);
    printf("philosopher %i is thinking\n", philo->philo_id);
    return (print(ph));
}

t_philo *philo_list_init(int time_to_eat, int time_to_sleep, int time_to_die, int number)
{
    int i;
    t_philo *philo;
    t_philo *tmp;
    t_philo  *start;

    philo = malloc(sizeof(t_philo));
    philo->time_to_eat = time_to_eat;
    philo->time_to_sleep = time_to_sleep;
    philo->time_to_die = time_to_die;
    philo->philo_id = 1;
    start = philo;
    i = 2;
    while (i <= number)
    {
        
        tmp = malloc(sizeof(t_philo));
        philo->next = tmp;
        philo = philo->next;
        philo->time_to_eat = time_to_eat;
        philo->time_to_sleep = time_to_sleep;
        philo->time_to_die = time_to_die;
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

void philo_mtx_accordance(t_philo *philo, t_mutex *mtx, long int time_start)
{
    philo->left = &mtx->mutex;
    philo->right = &mtx->prev->mutex;
    philo->time_of_last_meal = time_start;
    philo = philo->next;
    mtx = mtx->next;
    while (philo->philo_id != 1)
    {
        philo->left = &mtx->mutex;
        philo->right = &mtx->prev->mutex;
        philo->time_of_last_meal = time_start;
        philo = philo->next;
        mtx = mtx->next;
    }

}

int main()
{
    int number = 10;
    pthread_t arr[number];
    t_philo *philo;
    t_mutex *mtx;
    struct timeval tv;


    gettimeofday(&tv, NULL);
    printf("time %li : %li\n", tv.tv_sec, tv.tv_usec);

    philo = philo_list_init(3000000, 1000000, 4000000, number);
    mtx = mtx_list_init(number);
    philo_mtx_accordance(philo, mtx, tv.tv_sec);
    int i = 0;

    while (i < number)
    {
        pthread_create(&arr[i], NULL, print, (void*) philo);
        philo = philo->next;
        i++;
    }

    i = 0;
    while (i < number)
    {
        pthread_join(arr[i], NULL);
        i++;
    }

}