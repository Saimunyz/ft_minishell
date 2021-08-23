/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:05:18 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/23 11:26:09 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **cmd)
{
	g_error = 0;
	ft_change_term_mode(0);
	if (!cmd[1])
		exit(0);
	if (cmd[2])
	{
		printf("exit: %s: Too many arguments");
		exit(255);
	}
}
