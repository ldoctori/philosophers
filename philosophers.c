#include "philosophers.h"

void *print(void *ph)
{
    t_philo *philo = ph;
    
    pthread_mutex_lock(philo->right);
    if (die_check(philo) == 1)
    {
        pthread_mutex_unlock(philo->right);
        printf("%i philosopher %i died\n", get_time(philo), philo->philo_id);
        return (NULL);
    }
    printf("%i philosopher %i has taken right fork\n", get_time(philo), philo->philo_id);
    if (philo->left != philo->right)
        pthread_mutex_lock(philo->left);
    else
        usleep(philo->input->time_to_die*1000);
    if (die_check(philo) == 1)
    {
        pthread_mutex_unlock(philo->right);
        pthread_mutex_unlock(philo->left);
        printf("%i philosopher %i died\n", get_time(philo), philo->philo_id);
        return (NULL);
    }
    printf("%i philosopher %i has taken left fork\n", get_time(philo), philo->philo_id);
    
    printf("%i philosopher %i is eating\n", get_time(philo), philo->philo_id);
    philo->number_of_meal++;
    usleep(philo->input->time_to_eat * 1000);
    pthread_mutex_unlock(philo->right);
    pthread_mutex_unlock(philo->left);

    if (philo->input->max_number_of_meal > 0 && philo->number_of_meal >= philo->input->max_number_of_meal)
        return (NULL);

    gettimeofday(&philo->tv, NULL);
    philo->time_of_last_meal_sec = philo->tv.tv_sec;
    philo->time_of_last_meal_usec = philo->tv.tv_usec;
    printf("%i philosopher %i is sleeping\n", get_time(philo), philo->philo_id);
    usleep(philo->input->time_to_sleep * 1000);
    printf("%i philosopher %i is thinking\n", get_time(philo), philo->philo_id);
    return (print(ph));
}

int main(int argc, char **argv)
{
    t_input input;
    pthread_t **arr;
    t_philo *philo;
    t_mutex *mtx;
    struct timeval tv;
    int i = 0;

    if (argc < 5 || argc > 6)
        return (0);
    take_input(&input, ++argv);
    arr = arr_create(input.philo_num);
    philo = philo_list_init(&input);
    mtx = mtx_list_init(input.philo_num);
    gettimeofday(&tv, NULL);
    philo_mtx_accordance(philo, mtx, &tv);
    while (i < input.philo_num)
    {
        pthread_create(arr[i], NULL, print, (void*) philo);
        philo = philo->next;
        i++;
        usleep(100);
    }

    i = 0;
    while (i < input.philo_num)
    {
        pthread_join(*arr[i], NULL);
        i++;
    }

    free_philo(philo);
    free_destroy_mtx(mtx, input.philo_num);
    free_thread_arr(arr, input.philo_num);
}