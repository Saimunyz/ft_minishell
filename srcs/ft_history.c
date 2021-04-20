/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 02:29:53 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/20 13:30:06 by swagstaf         ###   ########.fr       */
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
	char	*home;

	if (*command == '\0')
		return ;
	home = ft_strjoin(getenv("HOME"), "/.minishell_history");
	fd = open(home, O_WRONLY|O_APPEND|O_CREAT, 0755);
	ft_check_errno();
	write(fd, command, ft_strlen(command));
	ft_check_errno();
	write(fd, "\n", 1);
	ft_check_errno();
	free(home);
	close(fd);
	ft_check_errno();
}

t_list	*ft_read_history(void)
{
	int		fd;
	char	*home;
	char	*line;
	int		ret;
	t_list	*hist;

	home = ft_strjoin(getenv("HOME"), "/.minishell_history");
	fd = open(home, O_RDONLY | O_CREAT, 0755);
	ft_check_errno();
	hist = NULL;
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		ft_lstadd_front(&hist, ft_lstnew(line));
		//free(line); НУжно ли чистить, или потом просто весь список чистить?
		ret = get_next_line(fd, &line);
	}
	if (*line != '\0')
		ft_lstadd_front(&hist, ft_lstnew(line));
	//free(line);
	free(home);
	close(fd);
	ft_check_errno();
	return (hist);
}

void	ft_put_history(int *len, char **line, int keycode, t_hist *hist)
{
	t_list	*tmp;

	tmp = hist->hist;
	if (!tmp)
		return ;
	ft_del_line(len, line);
	if (keycode == KEY_UP && tmp->next != NULL)
	{
		*line = ft_strdup((char *)tmp->content);
		*len = ft_strlen(*line);
		tmp = tmp->next;
	}
	else if (keycode == KEY_DOWN && hist->hist != hist->start)
	{
		while (tmp->next && tmp->next != hist->hist)
			tmp = tmp->next;
		*line = ft_strdup((char *)tmp->content);
		*len = ft_strlen(*line);
	}
	hist->hist = tmp;
	write(1, *line, *len);
}
