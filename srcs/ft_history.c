/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 02:29:53 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/20 16:25:29 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * как тут ошибки то обрабатывать?
 * переписать, нужно getenv отсюда вынести и хранить в глобальной переменной
 * отредактирвоать 777
 */

void	ft_write_history(char *command)
{
	int		fd;

	if (*command == '\0')
		return ;
	fd = open(g_var.path_hist, O_WRONLY|O_APPEND|O_CREAT, 0755);
	ft_check_errno();
	write(fd, command, ft_strlen(command));
	ft_check_errno();
	write(fd, "\n", 1);
	ft_check_errno();
	close(fd);
	ft_check_errno();
}

int	ft_flines_counter(char *filepath)
{
	int		fd;
	int		counter;
	char	*line;
	int		ret;

	fd = 0;
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		errno = 0;
		return (0);
	}
	counter = 0;
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		counter++;
		free(line);
		ret = get_next_line(fd, &line);
	}
	free(line);
	close(fd);
	return(counter);
}

char	*ft_read_history(int line_num)
{
	int		fd;
	char	*line;
	int		ret;
	char	*command;

	if (line_num == 0)
		return NULL;
	fd = open(g_var.path_hist, O_RDONLY);
	ft_check_errno();
	ret = get_next_line(fd, &line);
	while (ret > 0 && line_num-- - 1)
	{
		free(line);
		ret = get_next_line(fd, &line);
	}
	command = ft_strdup(line);
	while (ret > 0)
	{
		free(line);
		ret = get_next_line(fd, &line);
	}
	close(fd);
	ft_check_errno();
	return (command);
}



void	ft_put_history(int *len, char **line, int keycode, int *fsize)
{
	int		flen;

	flen = ft_flines_counter(g_var.path_hist);
	if (keycode == KEY_UP && *fsize > 0)
	{
		ft_del_line(len, line);
		*line = ft_read_history(*fsize);
		if (!*line)
			return ;
		*len = ft_strlen(*line);
		(*fsize)--;
		write(1, *line, *len);
	}
	else if (keycode == KEY_DOWN && *fsize < flen)
	{
		ft_del_line(len, line);
		if ((*fsize) == 0)
			(*fsize) = 1;
		*line = ft_read_history(++(*fsize));
		if (!*line)
			return ;
		*len = ft_strlen(*line);
		write(1, *line, *len);
	}
}
