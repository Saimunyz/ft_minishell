/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:03:39 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/31 22:16:46 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_local_command(char *command)
{
	int			st;
	struct stat	buf;

	st = stat(command, &buf);
	if (st == -1)
	{
		errno = 0;
		return (0);
	}
	else if (!(buf.st_mode & S_IXUSR))
	{
		printf("%s: Permission denied\n", command);
		g_error = 126;
	}
	else if (buf.st_mode & S_IFDIR)
	{
		printf("%s: Is a directory\n", command);
		g_error = 126;
	}
	return (command);
}

char	*ft_find_command(char *command, char **path)
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
	ft_putstr_fd(tmp_str, 2);
	free(tmp_str);
}

t_l_cmd	command_if_l_cmd(t_cmd *a_cmd, int i, t_l_cmd l_cmds, int *not_found)
{
	if (l_cmds.cmd || l_cmds.aur_cmd || a_cmd[i].files || l_cmds.local_cmd)
		*not_found = 0;
	if (l_cmds.local_cmd)
		a_cmd[i].cmd[0] = l_cmds.local_cmd;
	else if (l_cmds.cmd)
	{
		free(a_cmd[i].cmd[0]);
		a_cmd[i].cmd[0] = l_cmds.cmd;
	}
	return (l_cmds);
}

void	command_fork(t_cmd *a_cmd, int i, t_l_cmd l_cmds)
{
	pid_t	pid;
	int		status;
	int		not_found;

	not_found = 1;
	l_cmds = command_if_l_cmd(a_cmd, i, l_cmds, &not_found);
	if (!ft_strncmp(a_cmd->cmd[0], "./minishell", ft_strlen(a_cmd->cmd[0])))
		ft_turn_signals(0);
	pid = fork();
	if (pid == 0)
	{
		errno = 0;
		command_pid(a_cmd, i, &l_cmds, not_found);
	}
	commands_close(a_cmd, i);
	waitpid(pid, &status, 0);
	if (g_error != 130 && g_error != 131 && g_error != 126)
		g_error = WEXITSTATUS(status);
	if (a_cmd[i].cmd[0] && !l_cmds.aur_cmd && !l_cmds.local_cmd \
			&& !l_cmds.cmd && a_cmd[i].cmd[0][0] != 0)
		ft_command_not_found(a_cmd[i].cmd[0]);
	ft_turn_signals(1);
}
