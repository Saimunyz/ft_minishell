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

	if (ft_find_aur_command(command))
		return ft_find_aur_command(command);
	tmp_path = path;
	while (*path)
	{
		tmp_cmd = ft_strjoin(*path, "/");
		cmd = ft_strjoin(tmp_cmd, command);
		free(tmp_cmd);
		st = stat(cmd, &buf); //TODO это что и откуда?
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


void ft_commands(t_cmd *a_cmd, int i, t_memory *mem)
{
	pid_t pid;
	char *cmd;
	char *local_cmd;
	char *aur_cmd;
	int status;
	int not_found;
	char **env;

	env = ft_lst2str(mem->env);
	not_found = 1;
	local_cmd = NULL;
	aur_cmd = NULL;
	cmd = NULL;
	if (i == 0 && (ft_strlen(a_cmd[0].cmd[0]) != 0 && (!ft_strncmp(a_cmd[0].cmd[0], "exit", ft_strlen(a_cmd[0].cmd[0]))
		|| (!ft_strncmp(a_cmd[0].cmd[0], "cd", ft_strlen(a_cmd[0].cmd[0])))
											|| (!ft_strncmp(a_cmd[0].cmd[0], "export", ft_strlen(a_cmd[0].cmd[0])))
											|| (!ft_strncmp(a_cmd[0].cmd[0], "unset", ft_strlen(
			a_cmd[0].cmd[0])))))) //костыльный костыль, но и пофиг
	{
		if (i == 0)
		{ //а тут надо только для 0 команды? а если это вторая, десятая? не проходит a=1 | ls
			ft_start_commands(a_cmd[i].cmd, mem, 0, env);
			ft_clear_arr(a_cmd[i].cmd);
			ft_clear_arr(env);
			return;
		}
	}
//	if (a_cmd[i].cmd[0][0] == '.' || a_cmd[i].cmd[0][0] == '/')
	if (a_cmd[i].cmd[0] && (a_cmd[i].cmd[0][0] == '.' || a_cmd[i].cmd[0][0] == '/'))
	{
		local_cmd = ft_find_local_command(a_cmd[i].cmd[0]);
		if (!local_cmd)
		{
			ft_command_not_found(a_cmd[i].cmd[0]);
			if (!a_cmd[i].files)
				ft_clear_arr(a_cmd[i].cmd);
			ft_clear_arr(env);
			return;
		}
	}
	if (!local_cmd)
		aur_cmd = ft_find_aur_command(a_cmd[i].cmd[0]);
	if (!aur_cmd && !local_cmd)
	{
		if (!ft_getenv("PATH", mem)) //21.08.21
			cmd = NULL;
		else
			cmd = ft_find_command(a_cmd[i].cmd[0], ft_split(ft_getenv("PATH", mem), ':')); //21.08.21
	}
	if (cmd || aur_cmd || a_cmd[i].files || local_cmd)
		not_found = 0;
//	g_error = 0; //todo прверять на ошибки, надо переписывать иначе затирает 126 которая приходит из кейса ./неИсплняемыйФайл
	if (aur_cmd)
	{
		if (!a_cmd[i].files)
		{
			free(a_cmd[i].cmd[0]);
			a_cmd[i].cmd[0] = aur_cmd;
		}
	}
	else if (local_cmd)
		a_cmd[i].cmd[0] = local_cmd;
	else if (cmd)
	{
		free(a_cmd[i].cmd[0]); //TODO вынести из if проверить что нет утечки.
		a_cmd[i].cmd[0] = cmd;
	}
	pid = fork();
	if (pid == 0)
	{
		if (a_cmd[i].files)
		{
			ft_redirect(a_cmd, mem);
			exit(0);
		} else if (a_cmd[i].p_next && a_cmd[i].p_priv)
		{
			dup2(a_cmd[i - 1].fd[0], 0);
			close(a_cmd[i - 1].fd[0]);
			close(a_cmd[i - 1].fd[1]);
			dup2(a_cmd[i].fd[1], 1);
			close(a_cmd[i].fd[0]);
			close(a_cmd[i].fd[1]);
			ft_start_commands(a_cmd[i].cmd, mem, not_found, env);
			exit(0);
		} else if (a_cmd[i].p_next)
		{
			dup2(a_cmd[i].fd[1], 1);
			close(a_cmd[i].fd[0]);
			close(a_cmd[i].fd[1]);
			ft_start_commands(a_cmd[i].cmd, mem, not_found, env);
			exit(0);

		} else if (a_cmd[i].p_priv)
		{
			dup2(a_cmd[i - 1].fd[0], 0);
			close(a_cmd[i - 1].fd[0]);
			close(a_cmd[i - 1].fd[1]);
			ft_start_commands(a_cmd[i].cmd, mem, not_found, env);
			exit(0);
		} else
		{
			close(a_cmd[i].fd[0]);
			close(a_cmd[i].fd[1]);
			ft_start_commands(a_cmd[i].cmd, mem, not_found, env);
			exit(0);
		}
	}

	if (a_cmd[i].files != 0)
	{

	} else if (a_cmd[i].p_next && a_cmd[i].p_priv)
	{
		close(a_cmd[i - 1].fd[0]);
		close(a_cmd[i].fd[1]);
	} else if (a_cmd[i].p_next)
	{
		close(a_cmd[i].fd[1]);
	} else if (a_cmd[i].p_priv)
	{
		close(a_cmd[i - 1].fd[0]);
		close(a_cmd[i].fd[0]);
		close(a_cmd[i].fd[1]);
	} else
	{
		close(a_cmd[i].fd[0]); // TODO не факто что нужно
		close(a_cmd[i].fd[1]);
	}
	waitpid(pid, &status, 0);
	if (g_error != 130 && g_error != 131 && g_error != 126)
		g_error = WEXITSTATUS(status);
	if (!aur_cmd && !local_cmd && !cmd)
		ft_command_not_found(a_cmd[i].cmd[0]);

	if (!a_cmd[i].files)
		ft_clear_arr(a_cmd[i].cmd);
	ft_clear_arr(env);
}
