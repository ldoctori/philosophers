#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	number;
	int	sign;

	number = 0;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while ('9' >= *str && *str >= '0')
	{
		number = number * 10 + (*str - '0');
		str++;
	}
	return (number * sign);
}
