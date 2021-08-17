#include "minishell.h"

void ft_clear_arr(char **arr) {
	char *tmp;
	char **tmp_arr;

	if (!arr)
		return;
	tmp_arr = arr;
	while (*arr) {
		tmp = *arr;
		arr++;
		free(tmp);
	}
	free(tmp_arr);
}

char *ft_find_aur_command(char *command) {
	int splt_len;

	splt_len = ft_strlen(command);

	if (!ft_strncmp(command, "pwd", ft_strlen(command)) && splt_len != 0)
		return "pwd";
	else if (!ft_strncmp(command, "echo", ft_strlen(command)) && splt_len != 0)
		return "echo";
	else if (!ft_strncmp(command, "cd", ft_strlen(command)) && splt_len != 0)
		return "cd";
	else if (!ft_strncmp(command, "exit", ft_strlen(command)) && splt_len != 0)
		ft_exit();
	else if (!ft_strncmp(command, "env", ft_strlen(command)) && splt_len != 0)
		return "env";
	else if (!ft_strncmp(command, "export", ft_strlen(command)) && splt_len != 0)
		return "export";
	else if (!ft_strncmp(command, "unset", ft_strlen(command)) && splt_len != 0)
		return "unset";
	return (0);
}

char *ft_find_command(char *command, char **path) {
	int st;
	struct stat buf;
	char *tmp_cmd;
	char *cmd;
	char **tmp_path;

	if (ft_find_aur_command(command))
		return ft_find_aur_command(command);
	tmp_path = path;
	while (*path) {
		tmp_cmd = ft_strjoin(*path, "/");
		cmd = ft_strjoin(tmp_cmd, command);
		free(tmp_cmd);
		st = stat(cmd, &buf); //TODO это что и откуда?
		if (st == -1)
			errno = 0;
		else {
			ft_clear_arr(tmp_path);
			return (cmd);
		}
		path++;
		free(cmd);
	}
	ft_clear_arr(tmp_path);
	return (0);
}

void ft_command_not_found(char *cmd) {
	char *tmp_str;

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
//void ft_commands(char **splt, t_pipe *fd) {
void ft_commands(t_cmd *a_cmd, int i, t_memory *mem) {
	pid_t pid;
	char *cmd;
	char *aur_cmd;
	int status;

	if ((!ft_strncmp(a_cmd[0].cmd[0], "cd", ft_strlen(a_cmd[0].cmd[0])))
		|| (!ft_strncmp(a_cmd[0].cmd[0], "export", ft_strlen(a_cmd[0].cmd[0])))
		|| (!ft_strncmp(a_cmd[0].cmd[0], "unset", ft_strlen(a_cmd[0].cmd[0]))))  //костыльный костыль, но и пофиг
	{
		if (i == 0)
			ft_start_commands(a_cmd[i].cmd, mem);
		return;
	}

	aur_cmd = ft_find_aur_command(a_cmd[i].cmd[0]);


	if (!aur_cmd)
		cmd = ft_find_command(a_cmd[i].cmd[0], ft_split(getenv("PATH"), ':'));
	if (cmd || aur_cmd) {
		g_error = 0;
		if (aur_cmd)
			a_cmd[i].cmd[0] = aur_cmd;
		else {
			free(a_cmd[i].cmd[0]); //TODO вынести из if проверить что нет утечки.
			a_cmd[i].cmd[0] = cmd;
		}
		pid = fork();
		if (pid == 0) {
			if (a_cmd[i].p_next && a_cmd[i].p_priv) {
				dup2(a_cmd[i - 1].fd[0], 0);
				close(a_cmd[i - 1].fd[0]);
				close(a_cmd[i - 1].fd[1]);
				dup2(a_cmd[i].fd[1], 1);
				close(a_cmd[i].fd[0]);
				close(a_cmd[i].fd[1]);
				ft_start_commands(a_cmd[i].cmd, mem);
				exit(0);
			} else if (a_cmd[i].p_next) {
				dup2(a_cmd[i].fd[1], 1);
				close(a_cmd[i].fd[0]);
				close(a_cmd[i].fd[1]);
				ft_start_commands(a_cmd[i].cmd, mem);
				exit(0);

			} else if (a_cmd[i].p_priv) {
				dup2(a_cmd[i - 1].fd[0], 0);
				close(a_cmd[i - 1].fd[0]);
				close(a_cmd[i - 1].fd[1]);
				ft_start_commands(a_cmd[i].cmd, mem);
				exit(0);
			} else if (a_cmd[i].files) {
				ft_redirect(a_cmd, mem);
				exit(0);
			} else { // Выше сделать как внизу
				close(a_cmd[i].fd[0]);
				close(a_cmd[i].fd[1]);
				ft_start_commands(a_cmd[i].cmd, mem);
				exit(0);
			}
		}

		if (a_cmd[i].p_next && a_cmd[i].p_priv) {
			close(a_cmd[i - 1].fd[0]);
			close(a_cmd[i].fd[1]);
		} else if (a_cmd[i].p_next) {
			close(a_cmd[i].fd[1]);
		} else if (a_cmd[i].p_priv) {
			close(a_cmd[i - 1].fd[0]);
			close(a_cmd[i].fd[0]);
			close(a_cmd[i].fd[1]);
		} else if (a_cmd[i].files)
		{

		}
		else {
			close(a_cmd[i].fd[0]); // TODO не факто что нужно
			close(a_cmd[i].fd[1]);
		}
		waitpid(pid, &status, 0);
	} else
		ft_command_not_found(a_cmd[i].cmd[0]);
}
