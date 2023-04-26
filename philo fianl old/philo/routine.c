/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:32:49 by atuliara          #+#    #+#             */
/*   Updated: 2023/04/26 15:01:19 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Join, destroy and free.
*/

void	exit_routine(t_rules *rules, t_philosopher *philo)
{
	int i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&(rules->philosophers->forks[i]));
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&(rules->death));
	pthread_mutex_destroy(&(rules->print));
	pthread_mutex_destroy(&(rules->eating));
	free(rules->philosophers);
	free(rules->philosophers->forks);
}

void change_all_ate(t_rules *rules)
{
	pthread_mutex_lock(&(rules->satisfied));
	rules->all_ate = 1;
	pthread_mutex_unlock(&(rules->satisfied));
}

/*
** The main thread stays in this function until someone has died or everybody has eaten the required amount.
*/

void	check_if_dead(t_rules *rules, t_philosopher *philo)
{
	int i;

	while (!is_satisfied(rules))
	{
		i = -1;
		while (!is_dead(rules) && ++i < rules->nb_philo)
		{
			pthread_mutex_lock(&(rules->eating));
			if ((timestamp() - philo[i].t_last_meal) > rules->time_death)
			{
				philo_print(rules, i, "died");
				pthread_mutex_lock(&(rules->death));
				rules->dead = 1;
				pthread_mutex_unlock(&(rules->death));
			}
			pthread_mutex_unlock(&(rules->eating));
		}
	if (is_dead(rules))
		break ;
	i = 0;
	while (rules->nb_eat != -1 && i < rules->nb_philo && philo[i].times_eaten >= rules->nb_eat)
		i++;
	if (i == rules->nb_philo)
		change_all_ate(rules);
	}
}

void	philo_eats(t_philosopher *philo)
{
	t_rules *rules;

	rules = philo->rules;

	pthread_mutex_lock(&(rules->philosophers->forks[philo->left_fork_id]));
	philo_print(rules, philo->id, "has taken a fork");
	if (rules->nb_philo == 1)
		pthread_detach(philo->thread_id);
	pthread_mutex_lock(&(rules->philosophers->forks[philo->right_fork_id]));
	philo_print(rules, philo->id, "has taken a fork");		
	pthread_mutex_lock(&(rules->eating));
	philo_print(rules, philo->id, "is eating");
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(rules->eating));
	sleep_until(rules->time_eat, rules);
	philo->times_eaten++;
	pthread_mutex_unlock(&(rules->philosophers->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(rules->philosophers->forks[philo->right_fork_id]));
}

void	*actions(void *philosopher)
{
	int				i;
	t_philosopher	*philo;
	t_rules			*rules;

	i = 0;
	philo = (t_philosopher *)philosopher;
	rules = philo->rules;
	if (philo->id % 2)
		sleep_until(rules->time_eat / 10, rules);
	while (is_dead(rules) == 0)
	{
		philo_eats(philo);
		if (is_satisfied(rules))
			break ;
		philo_print(rules, philo->id, "is sleeping");
		sleep_until(rules->time_sleep, rules);
		philo_print(rules, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

/*
** Launch the routine for each thread and pass the philo struct as argument for the "actions" function.
*/

int		launch(t_rules *rules)
{
	t_philosopher	*philo;
	int				i;

	i = 0;
	philo = rules->philosophers;
	rules->start_time = timestamp();
	while (i < rules->nb_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, actions, &(philo[i])))
			return (1);
		philo[i].t_last_meal = timestamp();
		i++;
	}
	check_if_dead(rules, rules->philosophers);
	exit_routine(rules, philo);
	return (0);
}
