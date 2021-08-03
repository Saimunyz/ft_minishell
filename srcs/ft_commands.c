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

char *ft_find_command(char *command, char **path) {
	int st;
	struct stat buf;
	char *tmp_cmd;
	char *cmd;
	char **tmp_path;

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
void ft_commands(char **splt, t_pipe *fd) {
	pid_t pid;
	char *cmd;
	char *newenviron[0];

	//TODO всегда можно NULL или нет?
	newenviron[0] = NULL;
	//TODO паф могут удалить, не должно крашится. проверить когда допишем
	cmd = ft_find_command(splt[0], ft_split(getenv("PATH"), ':'));
	if (cmd) {
		g_error = 0;
		free(splt[0]); //TODO вынести из if проверить что нет утечки.
		splt[0] = cmd;



		pid = fork();


		if (pid == 0) {

			//++
			if (fd->order == 0) {
				dup2(fd->fd[1], 1);
				close(fd->fd[0]);
				char ch = '0' + fd->fd[1];
				write(2, &ch, 1);
				ft_putstr_fd("\nFrom hell1!\n", 2);
			}
			else {
//				dup2(fd->fd[0], 0);
//				char ch = '0' + fd->fd[0];
//				write(1, &ch, 1);
//				ft_putstr_fd("\nFrom hell2!\n", 1);
//				close(fd -> fd[1]);
			}
			//--

			execve(cmd, splt, newenviron);
			//++
//			close(fd -> fd[1]);
			if (fd->order == 0) {
//				close(fd->fd[0]);
//				close(fd -> fd[1]);
			} else
			{
				ft_putstr_fd("\nexecve 2!\n", 1);
//				close(fd -> fd[1]);
//				close(fd->fd[0]);
			}
			//--

			exit(0);

		} else {
//			dup2(fd->fd[0], 0);
//			close(fd -> fd[1]);
		}
		wait(&pid);

		if (fd->order == 0) {
			dup2(fd->fd[0], 0);
			char ch = '0' + fd->fd[0];
			write(1, &ch, 1);
//			close(fd->fd[1]);
			ft_putstr_fd("\nFrom heaven2\n", 1);
		}
//		if (fd->order > 0)
//			close(fd->fd[0]);


//		close(fd->fd[0]);
		//++
//		if (fd->order != 0) {
//			close(fd->fd[0]);
//			close(fd->fd[1]);
//		}

		fd->order++;
		//--
	} else
		ft_command_not_found(splt[0]);
}
