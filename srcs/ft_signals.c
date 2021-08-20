/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:41:37 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/21 00:22:52 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_sigint(char **line, char *character)
{
	if (*character == '\3')
	{
		free(*line);
		*line = ft_strdup("\3");
		g_error = 130;
		return (1);
	}
	return (0);
}

void	ft_check_eof(char **line, char *character, t_hist *hist)
{
	if (*character == '\4' && **line == '\0')
	{
		ft_putstr_fd("exit\n", 1);
		free(*line);
		free(character);
		ft_lstclear(&hist->start, free);
		ft_change_term_mode(0);
		exit(0);
	}
}

void	ft_sigquit_handler(int num)
{
	g_error = num;
	g_error = 131;
	ft_putstr_fd("Quit\n", 1);
	//ft_exit();
}

void	ft_sigint_handler(int num)
{
	g_error = num;
	g_error = 130;
	ft_putstr_fd("\n", 1);
	//ft_exit();
}
