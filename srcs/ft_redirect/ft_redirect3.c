/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 21:08:10 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/31 21:14:56 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redirect_else(t_cmd *cmd, int i)
{
	if (cmd->p_priv && cmd-> p_next)
	{
		dup2(cmd[i].fd[1], 1);
		close(cmd[i].fd[0]);
		close(cmd[i].fd[1]);
	}
	else if (cmd->p_next && !cmd->p_priv)
	{
		dup2(cmd->fd[1], 1);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
	}
}

void	ft_left_double_redirect(t_cmd *cmd, int i)
{
	int	fd;

	if (cmd->p_priv)
	{
		dup2(cmd[i - 1].fd[0], 0);
		close(cmd[i - 1].fd[0]);
		close(cmd[i - 1].fd[1]);
	}
	else if (cmd->p_priv && cmd-> p_next)
	{
		dup2(cmd[i - 1].fd[0], 0);
		close(cmd[i - 1].fd[0]);
		close(cmd[i - 1].fd[1]);
	}
	fd = open(".temporary", O_RDONLY, 0755);
	dup2(fd, 0);
	close(fd);
	ft_redirect_else(cmd, i);
}
