/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:00:34 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/29 18:06:18 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_pipe(t_cmd **a_cmd, int i)
{
	if ((*a_cmd)[i].p_next)
	{
		(*a_cmd)[i].p_next = 0;
		if ((*a_cmd)[i + 1].p_priv)
		{
			(*a_cmd)[i + 1].p_priv = 0;
		}
	}
}

void	clear_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
}

void	clear_a_cmd(t_cmd *a_cmd, int i)
{
	int	j;

	j = 0;
	while (a_cmd[i].cmd[j])
		free(a_cmd[i].cmd[j++]);
	free(a_cmd[i].cmd);
}

int	ft_parse_command(t_cmd *a_cmd, int i, t_memory *mem)
{
	if (a_cmd[i].cmd[0] && a_cmd[i].cmd[0][0] == '\3')
	{
		ft_clear_arr(a_cmd[i].cmd);
		free(a_cmd);
		return (1);
	}
//	if (!a_cmd[i].red)  //todo вернул 31.08.21 Утечки!
		ft_commands(a_cmd, i, mem);
//	if (a_cmd[i].echo)
//		clear_a_cmd(a_cmd, i);
	return (0);
}

void	ft_parse(char *line, char *home, t_memory *mem)
{
	t_cmd	*a_cmd;
	int		i;

	i = 0;
	a_cmd = ft_split_string(line, mem);
	ft_write_history(line, home);
	while (a_cmd && a_cmd[i].cmd)
	{
		if (a_cmd[i].red)
		{
			i++;
			continue;
		}
		if (ft_variables(a_cmd[i].cmd, mem))
		{
			clear_a_cmd(a_cmd, i);
			a_cmd[i].cmd = (char **) malloc(sizeof(char *) * 2);
			a_cmd[i].cmd[0] = ft_strdup("");
			a_cmd[i].cmd[1] = NULL;
		}
		if (ft_parse_command(a_cmd, i, mem))
			return ;
		i++;
	}
	if (line && line[0] == '\0')
		g_error = 0;
	free(a_cmd);
}
