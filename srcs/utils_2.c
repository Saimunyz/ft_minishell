/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:05:58 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/16 16:48:14 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_term_action(char *action, int *len, char **line)
{
	char	buf[100];
	char	*buffer;
	char	*tmp;

	if (*len > 12)
	{
		buffer = buf;
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr(action, &buffer), 1, ft_putchar);
		buffer = buf;
		ft_bzero(buffer, 100);
		(*len)--;
	}
	tmp = ft_substr(*line, 0, *(len) - 12);
	free(*line);
	*line = tmp;
}
