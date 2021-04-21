/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 02:29:53 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/21 14:52:02 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write_history(char *command)
{
	int		fd;

	if (*command == '\0')
		return ;
	fd = open(g_var.path_hist, O_WRONLY | O_APPEND | O_CREAT, 0755);
	ft_check_errno();
	write(fd, command, ft_strlen(command));
	ft_check_errno();
	write(fd, "\n", 1);
	ft_check_errno();
	close(fd);
	ft_check_errno();
}

t_list	*ft_read_history(void)
{
	int		fd;
	char	*line;
	int		ret;
	t_list	*tmp;

	tmp = NULL;
	fd = open(g_var.path_hist, O_RDONLY);
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
	ft_check_errno();
	return (tmp);
}

void	ft_put_history_down(int *len, char **line, t_list **hist, t_list *strt)
{
	t_list	*tmp_strt;
	t_list	*tmp_hist;

	tmp_hist = *hist;
	tmp_strt = strt;
	if (!tmp_strt)
		return ;
	if (tmp_hist!= strt)
	{
		free(tmp_hist->content);
		tmp_hist->content = ft_strdup(*line);
		ft_del_line(len, line);
		while (tmp_strt->next && tmp_strt->next != tmp_hist)
			tmp_strt = tmp_strt->next;
		*line = ft_strdup((char *)tmp_strt->content);
		*len = ft_strlen(*line);
		write(1, *line, *len);
		*hist = tmp_strt;
	}
}

void	ft_put_history_up(int *len, char **line, t_list **hist)
{
	t_list	*tmp;

	tmp = *hist;
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
		*hist = tmp;
	}
}
