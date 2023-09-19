/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:33:08 by atuliara          #+#    #+#             */
/*   Updated: 2023/07/14 13:39:56 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_philosopher
{
	int					id;
	int					times_eaten;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	int					dead;
	pthread_t			thread_id;
	struct s_rules		*rules;
}						t_philosopher;

typedef struct s_rules
{
	int					nb_philo;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					nb_eat;
	int					all_ate;
	long long			start_time;
	pthread_mutex_t		death[4069];
	pthread_mutex_t		forks[4069];
	pthread_mutex_t		satisfied;
	pthread_mutex_t		eating;
	pthread_mutex_t		print;
	pthread_mutex_t		times_eaten_m;
	t_philosopher		philosophers[220];
}						t_rules;

void		death_occurred(t_rules *rules, int i);
int			is_satisfied(t_rules *rules);
int			error(char *str);
int			init_all(t_rules *rules, char **argv);
int			ft_atoi(const char *str);
void		philo_print(t_rules *rules, int id, char *string);
long long	timestamp(void);
int			launch(t_rules *rules);
void		exit_routine(t_rules *rules, t_philosopher *philo);
int			is_dead(t_rules *rules, int i);
void		sleep_until(long long time, t_rules *rules, t_philosopher *philo);
void		change_all_ate(t_rules *rules);

#endif
