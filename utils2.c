/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:38:25 by atuliara          #+#    #+#             */
/*   Updated: 2023/07/13 17:07:57 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_rules *rules, int i)
{
	pthread_mutex_lock(&(rules->death[i]));
	if (rules->philosophers[i].dead == 1)
	{
		pthread_mutex_unlock(&(rules->death[i]));
		return (1);
	}
	pthread_mutex_unlock(&(rules->death[i]));
	return (0);
}

void	death_occurred(t_rules *rules, int i)
{
	philo_print(rules, i, "died");
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(&(rules->death[i]));
		rules->philosophers[i].dead = 1;
		pthread_mutex_unlock(&(rules->death[i]));
		i++;
	}
}

void	change_all_ate(t_rules *rules)
{
	pthread_mutex_lock(&(rules->satisfied));
	rules->all_ate = 1;
	pthread_mutex_unlock(&(rules->satisfied));
}
