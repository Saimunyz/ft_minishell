/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:05:58 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/20 02:03:57 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_del_char(int *len, char **line)
{
	char	buf[100];
	char	*buffer;
	char	*tmp;

	if ((*len) + 12 > 12)
	{
		buffer = buf; // нужен ли буффер?
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dc", &buffer), 1, ft_putchar);
		buffer = buf;
		ft_bzero(buffer, 100);
		(*len)--;
	}
	tmp = ft_substr(*line, 0, *len);
	free(*line);
	*line = tmp;
}

void	ft_del_line(int *len, char **line)
{
	char	buf[100];
	char	*buffer;

	buffer = buf; // нужен ли буффер?
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tgetstr("cd", &buffer), 1, ft_putchar);
	buffer = buf;
	ft_bzero(buffer, 100);
	free(*line);
	*len = 0;
	*line = NULL;
}
