/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:05:58 by swagstaf          #+#    #+#             */
/*   Updated: 2021/05/05 14:55:56 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_del_char(int *len, char **line)
{
	char	*tmp;

	if ((*len) + 12 > 12)
	{
		tputs(tgetstr("ho", NULL), 1, ft_putchar);
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		(*len)--;
		tmp = ft_substr(*line, 0, *len);
		free(*line);
		*line = tmp;
		write(1, *line, *len);
	}
}

void	ft_del_line(int *len, char **line)
{
	tputs(tgetstr("ho", NULL), 1, ft_putchar);
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	free(*line);
	*len = 0;
	*line = NULL;
}

void	ft_print_bash_err(void)
{
	printf("minishell: %d: command not found\n", g_error);
	g_error = 127;
}
