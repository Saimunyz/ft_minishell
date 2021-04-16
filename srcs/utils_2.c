/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:05:58 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/16 15:13:50 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_term_action(char *action)
{
	char	buf[100];
	char	*buffer;

	buffer = buf;
	tputs(tgetstr(action, &buffer), 1, ft_putchar);
	buffer = buf;
	ft_bzero(buffer, 100);
}
