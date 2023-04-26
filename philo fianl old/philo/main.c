/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuliara <atuliara@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:33:16 by atuliara          #+#    #+#             */
/*   Updated: 2023/04/20 11:53:51 by atuliara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int free_all(t_rules *rules)
{
	if (rules->philosophers)
		free(rules->philosophers);
	if (rules->philosophers->forks)
		free(rules->philosophers->forks);
	return(1);
}

int	error(char *str)
{
	int len;

	len = 0;
	while (str[len])
		len++;
	write(2, "Error: ", 7);
	write(2, str, len);
	write(2, "\n", 1);
	return (1);
}

int		main(int argc, char **argv)
{
	t_rules	rules;
	
	if (argc != 5 && argc != 6)
	{
			error("Arguments");
			return(1);
	}
	if (init_all(&rules, argv))
		return(error("Init"));
 	launch(&rules);
	return (0);
}
