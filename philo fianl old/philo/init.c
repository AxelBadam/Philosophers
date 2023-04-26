/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:33:00 by atuliara          #+#    #+#             */
/*   Updated: 2023/04/26 14:39:29 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philosophers(t_rules *rules)
{
	int i;

	i = rules->nb_philo;
	while (--i >= 0)
	{
		rules->philosophers[i].id = i;
		rules->philosophers[i].times_eaten = 0;
		rules->philosophers[i].left_fork_id = i;
		rules->philosophers[i].right_fork_id = (i + 1) % rules->nb_philo;
		rules->philosophers[i].t_last_meal = 0;
		rules->philosophers[i].rules = rules;
	}
}

/*
** Ini mutex for each fork. Ini mutex for writing and 
*/

int	init_mutex(t_rules *rules)
{
	int i;

	i = rules->nb_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->philosophers->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(rules->print), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->eating), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->death), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->satisfied), NULL))
		return (1);
	return (0);
}

/*
** Allocate for the philo struct and fork mutexes.
*/

int allocate(t_rules *rules)
{
	rules->philosophers = malloc(sizeof(t_philosopher) * rules->nb_philo);
	rules->philosophers->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	if (rules->philosophers == NULL || rules->philosophers->forks == NULL)
		return(free_all(rules));
	return (0);
}

/*
** Initialize the rules and philosophers struct. Call mutex and philo init. 
*/

int	init_all(t_rules *rules, char **argv)
{
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_death = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		rules->nb_eat = ft_atoi(argv[5]);
		if (rules->nb_eat <= 0)
			return (1);
	}
	else
		rules->nb_eat = -1;
	rules->all_ate = 0;
	rules->dead = 0;
	if (allocate(rules))
		return(1);
	if (rules->nb_philo < 1 || rules->time_death < 0 || rules->time_eat < 0
		|| rules->time_sleep < 0 || rules->nb_philo > 200)
		return (1);
	if (init_mutex(rules))
		return (1);
	init_philosophers(rules);
	return (0);
}
