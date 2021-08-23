/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:05:18 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/23 12:59:39 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_exit_num(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(char **cmd)
{
	int	num;

	g_error = 0;
	ft_change_term_mode(0);
	if (!cmd[1])
		exit(0);
	if (ft_check_exit_num(cmd[1]))
	{
		printf("exit\n");
		printf("minishell$: exit: %s: numeric argument required\n", cmd[1]);
		exit(255);
	}
	num = ft_atoi(cmd[1]);
	if (num > 255)
		num = num % 256;
	if (cmd[2])
	{
		printf("exit\nminishell$: exit: too many arguments\n");
		exit(1);
	}
	printf("exit\n");
	exit(num);
}
