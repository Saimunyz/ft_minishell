#include "minishell.h"

void ft_clear_arr(char **arr)
{
	char *tmp;
	char **tmp_arr;

	if (!arr)
		return;
	tmp_arr = arr;
	while (*arr)
	{
		tmp = *arr;
		arr++;
		free(tmp);
	}
	free(tmp_arr);
}

char *ft_find_aur_command(char *command)
{
	int splt_len;

	splt_len = ft_strlen(command);
	if (!ft_strncmp(command, "pwd", ft_strlen(command)) && splt_len != 0)
		return ft_strdup("pwd");
	else if (!ft_strncmp(command, "echo", ft_strlen(command)) && splt_len != 0)
		return ft_strdup("echo");
	else if (!ft_strncmp(command, "cd", ft_strlen(command)) && splt_len != 0)
		return "cd";
		//else if (!ft_strncmp(command, "exit", ft_strlen(command)) && splt_len != 0)
		//	return ft_strdup("exit");
	else if (!ft_strncmp(command, "env", ft_strlen(command)) && splt_len != 0)
		return ft_strdup("env");
	else if (!ft_strncmp(command, "export", ft_strlen(command)) && splt_len != 0)
		return "export";
	else if (!ft_strncmp(command, "unset", ft_strlen(command)) && splt_len != 0)
		return "unset";
	return (0);
}

char *ft_find_local_command(char *command)
{
	int st;
	struct stat buf;

	st = stat(command, &buf); //TODO это что и откуда?
	if (st == -1)
	{
		errno = 0;
		return (0);
	}
	else if (!(buf.st_mode & S_IXUSR))
	{
		printf("%s: Permission denied\n", command); //todo перепроверить на маке
		g_error = 126;
	}
	else if (buf.st_mode & S_IFDIR)
	{
		printf("%s: Is a directory\n", command); //todo перепроверить на маке
		g_error = 0;
	}

	return (command);
}

char *ft_find_command(char *command, char **path)
{
	int st;
	struct stat buf;
	char *tmp_cmd;
	char *cmd;
	char **tmp_path;

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

void ft_command_not_found(char *cmd)
{
	char *tmp_str;

	g_error = 127;
	tmp_str = ft_strjoin(cmd, ": command not found\n");
	ft_putstr_fd(tmp_str, 2); //todo а в какой канал ошибку выводить? во второй?
	free(tmp_str);
}

///////////////////////////////////////////////////////////////////////////////
void com_pipe_1(t_cmd *a_cmd, int i, t_l_cmd *l_cmds, int not_found)
{
	dup2(a_cmd[i - 1].fd[0], 0);
	close(a_cmd[i - 1].fd[0]);
	close(a_cmd[i - 1].fd[1]);
	dup2(a_cmd[i].fd[1], 1);
	close(a_cmd[i].fd[0]);
	close(a_cmd[i].fd[1]);
	ft_start_commands(a_cmd[i].cmd, (*l_cmds).mem, not_found, (*l_cmds).env);
	exit(0);
}

void com_pipe_2(t_cmd *a_cmd, int i, t_l_cmd *l_cmds, int not_found)
{
	dup2(a_cmd[i].fd[1], 1);
	close(a_cmd[i].fd[0]);
	close(a_cmd[i].fd[1]);
	ft_start_commands(a_cmd[i].cmd, (*l_cmds).mem, not_found, (*l_cmds).env);
	exit(0);
}

void com_pipe_3(t_cmd *a_cmd, int i, t_l_cmd *l_cmds, int not_found)
{
	dup2(a_cmd[i - 1].fd[0], 0);
	close(a_cmd[i - 1].fd[0]);
	close(a_cmd[i - 1].fd[1]);
	ft_start_commands(a_cmd[i].cmd, (*l_cmds).mem, not_found, (*l_cmds).env);
	exit(0);
}

void command_no_pipe(t_cmd *a_cmd, int i, t_l_cmd *l_cmds, int not_found)
{
	close(a_cmd[i].fd[0]);
	close(a_cmd[i].fd[1]);
	ft_start_commands(a_cmd[i].cmd, (*l_cmds).mem, not_found, (*l_cmds).env);
	exit(0);
}

void command_pid(t_cmd *a_cmd, int i, t_l_cmd *l_cmds, int not_found)
{
	if (a_cmd[i].files)
	{
		ft_redirect(a_cmd, (*l_cmds).mem);
		exit(0);
	}
	else if (a_cmd[i].p_next && a_cmd[i].p_priv)
		com_pipe_1(a_cmd, i, l_cmds, not_found);
//	{
//		dup2(a_cmd[i - 1].fd[0], 0);
//		close(a_cmd[i - 1].fd[0]);
//		close(a_cmd[i - 1].fd[1]);
//		dup2(a_cmd[i].fd[1], 1);
//		close(a_cmd[i].fd[0]);
//		close(a_cmd[i].fd[1]);
//		ft_start_commands(a_cmd[i].cmd, (*l_cmds).mem, not_found, (*l_cmds).env);
//		exit(0);
//	}
	else if (a_cmd[i].p_next)
		com_pipe_2(a_cmd, i, l_cmds, not_found);
//	{
//		dup2(a_cmd[i].fd[1], 1);
//		close(a_cmd[i].fd[0]);
//		close(a_cmd[i].fd[1]);
//		ft_start_commands(a_cmd[i].cmd, (*l_cmds).mem, not_found, (*l_cmds).env);
//		exit(0);
//	}
			else
	if (a_cmd[i].p_priv)
		com_pipe_3(a_cmd, i, l_cmds, not_found);
//	{
//		dup2(a_cmd[i - 1].fd[0], 0);
//		close(a_cmd[i - 1].fd[0]);
//		close(a_cmd[i - 1].fd[1]);
//		ft_start_commands(a_cmd[i].cmd, (*l_cmds).mem, not_found, (*l_cmds).env);
//		exit(0);
//	}
	else
		command_no_pipe(a_cmd, i, l_cmds, not_found);
//	{
//		close(a_cmd[i].fd[0]);
//		close(a_cmd[i].fd[1]);
//		ft_start_commands(a_cmd[i].cmd, (*l_cmds).mem, not_found, (*l_cmds).env);
//		exit(0);
//	}
}




////////////////////////////////////////////////////////////////////////////////

t_l_cmd command_if_l_cmd(t_cmd *a_cmd, int i, t_l_cmd l_cmds, int *not_found)
{
	if (l_cmds.cmd || l_cmds.aur_cmd || a_cmd[i].files || l_cmds.local_cmd)
		*not_found = 0;
	if (l_cmds.aur_cmd)
	{
		if (!a_cmd[i].files)
		{
			free(a_cmd[i].cmd[0]);
			a_cmd[i].cmd[0] = l_cmds.aur_cmd;
		}
	}
	else if (l_cmds.local_cmd)
		a_cmd[i].cmd[0] = l_cmds.local_cmd;
	else if (l_cmds.cmd)
	{
		free(a_cmd[i].cmd[0]);
		a_cmd[i].cmd[0] = l_cmds.cmd;
	}
	return l_cmds;
}

void command_fork(t_cmd *a_cmd, int i, t_l_cmd l_cmds)
{
	pid_t pid;
	int status;
	int not_found;

	not_found = 1;
	l_cmds = command_if_l_cmd(a_cmd, i, l_cmds, &not_found);
	pid = fork();
	if (pid == 0)
		command_pid(a_cmd, i, &l_cmds, not_found);
	commands_close(a_cmd, i);
	waitpid(pid, &status, 0);
	if (g_error != 130 && g_error != 131 && g_error != 126)
		g_error = WEXITSTATUS(status);
	if (!l_cmds.aur_cmd && !l_cmds.local_cmd && !l_cmds.cmd)
		ft_command_not_found(a_cmd[i].cmd[0]);
}


///////////////////////////////////////////////////////////////////////////////////



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
//	char **env;
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
	if (!l_cmds.aur_cmd && !l_cmds.local_cmd)
		command_cmd(a_cmd, i, &l_cmds);
	command_fork(a_cmd, i, l_cmds);
	if (!a_cmd[i].files)
		ft_clear_arr(a_cmd[i].cmd);
	ft_clear_arr(l_cmds.env);
}


///////////////////////////////////////////////////////////////////