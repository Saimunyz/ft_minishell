/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:13:37 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/15 14:35:19 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_print_error(int type)
{
	ft_putstr_fd("Error\n", 2);
	if (type == GET_DATA_ERR)
		ft_putstr_fd("Could not access to the terminal data\n", 2);
	else
		ft_putstr_fd("UNKNOWN_ERR\n", 2);
	return (type);
}

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

int	ft_get_term_info(void)
{
	char	*term;
	int		ret;

	if (!isatty(STDIN_FILENO))
		return (ft_print_error(GET_DATA_ERR));
	//term = getenv("TERM");
	term = "xterm-256color"; // DEBUG ONLY
	if (term == 0)
		return (ft_print_error(GET_DATA_ERR));
	ret = tgetent(0, term);
	if (ret < 0 || ret == 0)
		return (ft_print_error(GET_DATA_ERR));
	return (0);
}
