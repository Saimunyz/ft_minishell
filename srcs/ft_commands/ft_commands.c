#include "minishell.h"

void commands_close(t_cmd *a_cmd, int i)
{
	if (a_cmd[i].files != 0)
	{
	}
	else if (a_cmd[i].p_next && a_cmd[i].p_priv)
	{
		close(a_cmd[i - 1].fd[0]);
		close(a_cmd[i].fd[1]);
	}
	else if (a_cmd[i].p_next)
	{
		close(a_cmd[i].fd[1]);
	}
	else if (a_cmd[i].p_priv)
	{
		close(a_cmd[i - 1].fd[0]);
		close(a_cmd[i].fd[0]);
		close(a_cmd[i].fd[1]);
	}
	else
	{
		close(a_cmd[i].fd[0]);
		close(a_cmd[i].fd[1]);
	}
}

int commands_1(t_cmd *a_cmd, int i, t_memory *mem, char **env)
{
	if (i == 0 && (ft_strlen(a_cmd[0].cmd[0]) != 0 && (!ft_strncmp(a_cmd[0].cmd[0], "exit", ft_strlen(a_cmd[0].cmd[0]))
													   ||
													   (!ft_strncmp(a_cmd[0].cmd[0], "cd", ft_strlen(a_cmd[0].cmd[0])))
													   || (!ft_strncmp(a_cmd[0].cmd[0], "export",
																	   ft_strlen(a_cmd[0].cmd[0])))
													   || (!ft_strncmp(a_cmd[0].cmd[0], "unset", ft_strlen(
			a_cmd[0].cmd[0]))))))
	{
		if (i == 0)
		{
			ft_start_commands(a_cmd[i].cmd, mem, 0, env);
			ft_clear_arr(a_cmd[i].cmd);
			ft_clear_arr(env);
			return (1);
		}
	}
	return (0);
}

int commands_2(t_cmd *a_cmd, int i, char **env, char **local_cmd)
{
	if (a_cmd[i].cmd[0] && (a_cmd[i].cmd[0][0] == '.' || a_cmd[i].cmd[0][0] == '/'))
	{
		*local_cmd = ft_find_local_command(a_cmd[i].cmd[0]);
		if (!(*local_cmd))
		{
			ft_command_not_found(a_cmd[i].cmd[0]);
			if (!a_cmd[i].files)
				ft_clear_arr(a_cmd[i].cmd);
			ft_clear_arr(env);
			return (1);
		}
	}
	return (0);
}

void command_cmd(t_cmd *a_cmd, int i, t_l_cmd *l_cmds)
{
	if (!ft_getenv("PATH", (*l_cmds).mem)) //21.08.21
		(*l_cmds).cmd = NULL;
	else if (!a_cmd[i].cmd[0])  //Сергей 25.08.21
		(*l_cmds).cmd = NULL;  //Сергей 25.08.21
	else
		(*l_cmds).cmd = ft_find_command(a_cmd[i].cmd[0], ft_split(ft_getenv("PATH", (*l_cmds).mem), ':')); //21.08.21
}

void ft_commands(t_cmd *a_cmd, int i, t_memory *mem)
{
	t_l_cmd l_cmds;

	l_cmds.mem = mem;
	l_cmds.env = ft_lst2str(mem->env);
	l_cmds.local_cmd = NULL;
	l_cmds.aur_cmd = NULL;
	l_cmds.cmd = NULL;
	if (commands_1(a_cmd, i, mem, l_cmds.env))
		return;
	if (commands_2(a_cmd, i, l_cmds.env, &l_cmds.local_cmd))
		return;
	if (a_cmd[i].echo)
		l_cmds.aur_cmd = a_cmd[i].cmd[0];
	if (!l_cmds.local_cmd && !a_cmd[i].echo && !a_cmd[i].red)
		l_cmds.aur_cmd = ft_find_aur_command(a_cmd[i].cmd[0]);
	g_error = 0;
	if (!l_cmds.aur_cmd && !l_cmds.local_cmd)
		command_cmd(a_cmd, i, &l_cmds);
	command_fork(a_cmd, i, l_cmds);
	if (!a_cmd[i].files)
		ft_clear_arr(a_cmd[i].cmd);
	ft_clear_arr(l_cmds.env);
}
