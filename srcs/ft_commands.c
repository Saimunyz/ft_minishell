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

/*
 * TODO буду рефакторить когда доделаем парсер
 * на данный моменет сделанно с огранничим количеством входящих параметров. Не более 1.
 * переписать когда разберемся с парсером... или наоброт :)
 * добавить ошибку если нет такой команды
 */
void	ft_commands(char **splt)
{
	pid_t	pid;
	char	*cmd;
	char	*newenviron[0];
	char	*newargv[3];//переписать под маллок

	//всегда можно NULL или нет?
	newenviron[0] = NULL;
	//паф могут удалить, не должно крашится. проверить когда допишем
	cmd = ft_find_command(splt[0], ft_split(getenv("PATH"), ':'));
	if (cmd)
	{
		newargv[0] = cmd;
		newargv[1] = splt[1];
		newargv[2] = NULL;
		pid = fork();
		if (pid == 0)
		{
			execve(cmd, newargv, newenviron);
			exit(0);
		}
		wait(&pid);
		free(cmd);
	}
	else
		ft_putstr_fd(ft_strjoin(splt[0], ": command not found\n"),1);
}
