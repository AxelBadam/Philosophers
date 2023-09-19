/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:32:49 by atuliara          #+#    #+#             */
/*   Updated: 2023/07/14 14:15:07 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Join and destroy.
*/

void	exit_routine(t_rules *rules, t_philosopher *philo)
{
	int	i;

	i = -1;
	if (rules->nb_philo == 1)
		pthread_detach(philo->thread_id);
	else
		while (++i < rules->nb_philo)
			pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&(rules->forks[i]));
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&(rules->death[i]));
	pthread_mutex_destroy(&(rules->print));
	pthread_mutex_destroy(&(rules->eating));
	pthread_mutex_destroy(&(rules->satisfied));
	pthread_mutex_destroy(&(rules->times_eaten_m));
}

/*
** The main thread stays in this function until someone
** has died or everybody has eaten the required amount.
*/

void	check_if_dead(t_rules *rules, t_philosopher *philo)
{
	int	i;

	while (!is_satisfied(rules))
	{
		i = 0;
		while (i < rules->nb_philo && !is_dead(rules, i))
		{
			pthread_mutex_lock(&(rules->eating));
			if ((timestamp() - philo[i].t_last_meal) > rules->time_death)
				death_occurred(rules, i);
			pthread_mutex_unlock(&(rules->eating));
			i++;
		}
		if (is_dead(rules, 0))
			break ;
		i = 0;
		pthread_mutex_lock(&(rules->times_eaten_m));
		while (rules->nb_eat != -1
			&& i < rules->nb_philo && philo[i].times_eaten >= rules->nb_eat)
			i++;
		pthread_mutex_unlock(&(rules->times_eaten_m));
		if (i == rules->nb_philo)
			change_all_ate(rules);
	}
}

void	philo_eats(t_philosopher *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
	philo_print(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->forks[philo->right_fork_id]));
	philo_print(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->eating));
	philo_print(rules, philo->id, "is eating");
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(rules->eating));
	sleep_until(rules->time_eat, rules, philo);
	pthread_mutex_lock(&(rules->times_eaten_m));
	philo->times_eaten++;
	pthread_mutex_unlock(&(rules->times_eaten_m));
	pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(rules->forks[philo->right_fork_id]));
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
		sleep_until(rules->time_eat / 2, rules, philo);
	while (!is_dead(rules, philo->id))
	{
		philo_eats(philo);
		if (is_satisfied(rules))
			break ;
		philo_print(rules, philo->id, "is sleeping");
		sleep_until(rules->time_sleep, rules, philo);
		philo_print(rules, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

/*
** Launch the routine for each thread and pass 
** the philo struct as argument for the "actions" function.
*/

int	launch(t_rules *rules)
{
	t_philosopher	*philo;
	int				i;

	i = 0;
	philo = rules->philosophers;
	rules->start_time = timestamp();
	while (i < rules->nb_philo)
	{
		philo[i].t_last_meal = timestamp();
		if (pthread_create(&(philo[i].thread_id), NULL, actions, &(philo[i])))
			return (1);
		i++;
	}
	check_if_dead(rules, philo);
	exit_routine(rules, philo);
	return (0);
}
