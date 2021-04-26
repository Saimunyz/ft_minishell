/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 02:29:53 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/24 01:00:43 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write_history(char *command, char *home)
{
	int		fd;
	char	*file_path;

	if (*command == '\0' || *command == '\3')
		return ;
	file_path = ft_strjoin(home, "/.minishell_history");
	fd = open(file_path, O_WRONLY | O_APPEND | O_CREAT, 0755);
	free(file_path);
	ft_check_errno();
	write(fd, command, ft_strlen(command));
	ft_check_errno();
	write(fd, "\n", 1);
	ft_check_errno();
	close(fd);
	ft_check_errno();
}

t_list	*ft_read_history(char *home)
{
	int		fd;
	char	*line;
	int		ret;
	t_list	*tmp;
	char	*file_path;

	tmp = NULL;
	file_path = ft_strjoin(home, "/.minishell_history");
	fd = open(file_path, O_RDONLY);
	free(file_path);
	if (fd == -1)
	{
		errno = 0;
		return (NULL);
	}
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		ft_lstadd_front(&tmp, ft_lstnew(line));
		ret = get_next_line(fd, &line);
	}
	free(line);
	ft_lstadd_front(&tmp, ft_lstnew(NULL));
	close(fd);
	return (tmp);
}

void	ft_put_history_down(int *len, char **line, t_hist *hist)
{
	t_list	*tmp_strt;
	t_list	*tmp_hist;

	tmp_hist = hist->hist;
	tmp_strt = hist->start;
	if (!tmp_strt)
		return ;
	if (tmp_hist != hist->start)
	{
		free(tmp_hist->content);
		tmp_hist->content = ft_strdup(*line);
		ft_del_line(len, line);
		while (tmp_strt->next && tmp_strt->next != tmp_hist)
			tmp_strt = tmp_strt->next;
		*line = ft_strdup((char *)tmp_strt->content);
		*len = ft_strlen(*line);
		write(1, *line, *len);
		hist->hist = tmp_strt;
	}
}

void	ft_put_history_up(int *len, char **line, t_hist *hist)
{
	t_list	*tmp;

	tmp = hist->hist;
	if (!tmp)
		return ;
	if (tmp->next != NULL)
	{
		free(tmp->content);
		tmp->content = ft_strdup(*line);
		ft_del_line(len, line);
		tmp = tmp->next;
		*line = ft_strdup((char *)tmp->content);
		*len = ft_strlen(*line);
		write(1, *line, *len);
		hist->hist = tmp;
	}
}
