/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:59:07 by gsmets            #+#    #+#             */
/*   Updated: 2023/04/26 14:40:34 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			sign;
	int long	res;

	sign = 1;
	res = 0;
	while (*str == '\n' || *str == '\t' || *str == '\f' || \
			*str == '\v' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		res = res * 10 + *str - '0';
		str++;
		if (res > 2147483648 && sign == -1)
			return (0);
		if (res > 2147483647 && sign == 1)
			return (-1);
	}
	return ((int)res * sign);
}

/*
** Combines the seconds and microseconds into a single value representing the total time in milliseconds.
*/

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void		sleep_until(long long time, t_rules *rules)
{
	long long past;

	past = timestamp();
	while ((is_dead(rules) == 0))
	{
		if ((timestamp() - past) >= time)
			break ;
		usleep(100);
	}
}

void		philo_print(t_rules *rules, int id, char *string)
{
	pthread_mutex_lock(&(rules->print));
	if ((is_dead(rules) == 0))
	{
		printf("%lli ", timestamp() - rules->start_time);
		printf("%i ", id + 1);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(rules->print));
	return ;
}

int	is_satisfied(t_rules *rules)
{
	pthread_mutex_lock(&(rules->satisfied));
	if (rules->all_ate == 1)
	{
		pthread_mutex_unlock(&(rules->satisfied));
		return (1);
	}
	pthread_mutex_unlock(&(rules->satisfied));
	return (0);
}

int	is_dead(t_rules *rules)
{
	pthread_mutex_lock(&(rules->death));
	if (rules->dead == 1)
	{
		pthread_mutex_unlock(&(rules->death));
		return (1);
	}
	pthread_mutex_unlock(&(rules->death));
	return (0);
}