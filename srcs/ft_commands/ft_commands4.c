/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:03:41 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/28 11:03:42 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup_pip_1(t_cmd *a_cmd, int i)
{
	dup2(a_cmd[i - 1].fd[0], 0);
	close(a_cmd[i - 1].fd[0]);
	close(a_cmd[i - 1].fd[1]);
	dup2(a_cmd[i].fd[1], 1);
	close(a_cmd[i].fd[0]);
	close(a_cmd[i].fd[1]);
}

void	ft_clear_arr(char **arr)
{
	char	*tmp;
	char	**tmp_arr;

	if (!arr)
		return ;
	tmp_arr = arr;
	while (*arr)
	{
		tmp = *arr;
		arr++;
		free(tmp);
	}
	free(tmp_arr);
}

char	*ft_find_aur_command(char *command)
{
	int	splt_len;

	splt_len = ft_strlen(command);
	if (!ft_strncmp(command, "pwd", ft_strlen(command)) && splt_len != 0)
		return (ft_strdup("pwd"));
	else if (!ft_strncmp(command, "echo", ft_strlen(command)) && splt_len != 0)
		return (ft_strdup("echo"));
	else if (!ft_strncmp(command, "cd", ft_strlen(command)) && splt_len != 0)
		return (ft_strdup("cd"));
	else if (!ft_strncmp(command, "env", ft_strlen(command)) && splt_len != 0)
		return (ft_strdup("env"));
	else if (!ft_strncmp(command, "export", \
		ft_strlen(command)) && splt_len != 0)
		return (ft_strdup("export"));
	else if (!ft_strncmp(command, "unset", ft_strlen(command)) && splt_len != 0)
		return (ft_strdup("unset"));
	return (0);
}
