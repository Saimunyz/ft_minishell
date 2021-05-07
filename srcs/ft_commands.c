/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 17:04:52 by swagstaf          #+#    #+#             */
/*   Updated: 2021/05/02 00:53:53 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_find_command(char	*command, char **path)
{
	int			st;
	struct stat	buf;
	char		*tmp_cmd;
	char		*cmd;
	char		**tmp_path;

	tmp_path = path;
	while (*path)
	{
		tmp_cmd = ft_strjoin(*path, "/");
		cmd = ft_strjoin(tmp_cmd, command);
		free(tmp_cmd);
		st = stat(cmd, &buf);
		if (st == -1)
			errno = 0;
		else
		{
			ft_clear_arr(tmp_path);
			return (cmd);
		}
		path++;
		free(cmd);
	}
	ft_clear_arr(tmp_path);
	return (0);
}

void	ft_command_not_found(char *cmd)
{
	char	*tmp_str;

	g_error = 127;
	tmp_str = ft_strjoin(cmd, ": command not found\n");
	ft_putstr_fd(tmp_str, 1);
	free(tmp_str);
}

/*
 * TODO В env нужно менять shlvl - это уровень вложенности, насколько глубоко залез терминал,
 * мы в минишел, так что изначально он 1, когда запустим что-то еще нужно увеличить на 1
 * TODO буду рефакторить когда доделаем парсер
 */
void	ft_commands(char **splt)
{
	pid_t	pid;
	char	*cmd;
	char	*newenviron[0];

	//TODO всегда можно NULL или нет?
	newenviron[0] = NULL;
	//TODO паф могут удалить, не должно крашится. проверить когда допишем
	cmd = ft_find_command(splt[0], ft_split(getenv("PATH"), ':'));
	if (cmd)
	{
		g_error = 0;
		splt[0] = cmd;
		pid = fork();
		if (pid == 0)
		{
			execve(cmd, splt, newenviron);
			exit(0);
		}
		wait(&pid);
	}
	else
		ft_command_not_found(splt[0]);
}
