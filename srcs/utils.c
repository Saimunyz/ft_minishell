/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:13:37 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/11 00:14:36 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_errno(void)
{
	if (errno != 0)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
}

void	ft_change_term_mode(t_term *term)
{
	struct termios	tmp;

	tmp = term->basic;
	term->basic = term->current;
	term->current = tmp;
	tcsetattr(0, TCSANOW, &term->current);
	ft_check_errno();
}
