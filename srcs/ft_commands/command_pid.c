/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:03:37 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/31 17:31:47 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	com_pipe_1(t_cmd *a_cmd, int i, t_l_cmd *l_cmds, int not_found)
{
	if (a_cmd[i].files && !a_cmd[i].red_err)
	{
		if (!a_cmd->red_d_l)
		{
			dup2(a_cmd[i - 1].fd[0], 0);
			close(a_cmd[i - 1].fd[0]);
			close(a_cmd[i - 1].fd[1]);
			dup2(a_cmd[i].fd[1], 1);
			close(a_cmd[i].fd[0]);
			close(a_cmd[i].fd[1]);
		}
		ft_redirect(a_cmd, (*l_cmds).mem, (*l_cmds).env, i);
		exit(0);
	}
	else
	{
		dup2(a_cmd[i - 1].fd[0], 0);
		close(a_cmd[i - 1].fd[0]);
		close(a_cmd[i - 1].fd[1]);
		dup2(a_cmd[i].fd[1], 1);
		close(a_cmd[i].fd[0]);
		close(a_cmd[i].fd[1]);
		ft_start_commands(a_cmd[i].cmd, (*l_cmds).mem, not_found, (*l_cmds).env);
	}
	exit(0);
}

void	com_pipe_2(t_cmd *a_cmd, int i, t_l_cmd *l_cmds, int not_found)
{
	if (a_cmd[i].files && !a_cmd[i].red_err)
	{
		if (!a_cmd->red_d_l)
		{
			dup2(a_cmd[i].fd[1], 1);
			close(a_cmd[i].fd[0]);
			close(a_cmd[i].fd[1]);
		}
		ft_redirect(a_cmd, (*l_cmds).mem, (*l_cmds).env, i);
		exit(0);
	}
	else
	{
		dup2(a_cmd[i].fd[1], 1);
		close(a_cmd[i].fd[0]);
		close(a_cmd[i].fd[1]);
		ft_start_commands(a_cmd[i].cmd, (*l_cmds).mem, not_found, (*l_cmds).env);
	}
	exit(0);
}

void	com_pipe_3(t_cmd *a_cmd, int i, t_l_cmd *l_cmds, int not_found)
{
	if (a_cmd[i].files && !a_cmd[i].red_err)
	{
		if (!a_cmd->red_d_l)
		{
			dup2(a_cmd[i - 1].fd[0], 0);
			close(a_cmd[i - 1].fd[0]);
			close(a_cmd[i - 1].fd[1]);
		}
		ft_redirect(a_cmd, (*l_cmds).mem, (*l_cmds).env, i);
		exit(0);
	}
	else
	{
		dup2(a_cmd[i - 1].fd[0], 0);
		close(a_cmd[i - 1].fd[0]);
		close(a_cmd[i - 1].fd[1]);
		ft_start_commands(a_cmd[i].cmd, (*l_cmds).mem, not_found, (*l_cmds).env);
	}
	exit(0);
}

void	command_no_pipe(t_cmd *a_cmd, int i, t_l_cmd *l_cmds, int not_found)
{
	close(a_cmd[i].fd[0]);
	close(a_cmd[i].fd[1]);
	if (a_cmd[i].files && !a_cmd[i].red_err)
	{
		ft_redirect(a_cmd, (*l_cmds).mem, (*l_cmds).env, i);
		exit(0);
	}
	else
		ft_start_commands(a_cmd[i].cmd, (*l_cmds).mem, not_found, (*l_cmds).env);
	exit(0);
}

void	command_pid(t_cmd *a_cmd, int i, t_l_cmd *l_cmds, int not_found)
{

	if (a_cmd[i].p_next && a_cmd[i].p_priv)
		com_pipe_1(a_cmd, i, l_cmds, not_found);
	else if (a_cmd[i].p_next)
		com_pipe_2(a_cmd, i, l_cmds, not_found);
	else if (a_cmd[i].p_priv)
		com_pipe_3(a_cmd, i, l_cmds, not_found);
	else
		command_no_pipe(a_cmd, i, l_cmds, not_found);
}
