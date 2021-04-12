/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:09:41 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/12 16:44:10 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init_term(t_term *term)
{
	tcgetattr(0, &term->basic);
	tcgetattr(0, &term->current);
	ft_check_errno();
	term->current.c_lflag &= ~(ECHO);
	term->current.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term->current);
	ft_check_errno();
}

static int	ft_extend_buff(char *line, int buff_size)
{
	buff_size += BUFF_SIZE;
	if (buff_size > 2147483647)
		buff_size = 2147483647;
	line = ft_realloc(line, buff_size);
	ft_check_errno();
	return (buff_size);
}

void	ft_check_command(char *line, int *all_len, int len)
{
	int	tmp;

	tmp = *all_len;
	if (!ft_strncmp(line, "\e[C", len))
	{
		if (tmp < *all_len)
			tmp++;
		else
			ft_is_int(len);
	}
	else if (!ft_strncmp(line, "\e[D", len))
		tmp++;
	else if (!ft_strncmp(line, "\e[B", len))
		printf("next\n");
	else if (!ft_strncmp(line, "\e[A", len))
		printf("previous\n");
	else
	{
		write(1, line, len);
		*all_len += len;
	}
}

void	ft_read(char *line)
{
	int		buff_size;
	int		len;
	int		all_len;

	all_len = 0;
	buff_size = BUFF_SIZE;
	line = (char *)malloc(sizeof(char) * buff_size);
	tgetent(0, TERM_NAME);
	ft_check_errno(); // Не все стандарты меняют ерно на маллок, возможн просто exit(1)
	while (1)
	{
		len = read(0, line, buff_size);
		ft_check_errno();
		ft_check_command(line, &all_len, len);
		if (!ft_strncmp(line, "\n", len))
			break;
		if (all_len > buff_size)
			buff_size = ft_extend_buff(line, buff_size);
	}
	write(1, "\n", 1);
}

void	ft_minishell(t_term *term)
{
	char	*line;

	line = NULL;
	ft_read(line);
	ft_change_term_mode(term);
	ft_check_errno();
	free(line);
}

int	main(void)
{
	t_term	term;

	errno = 0;
	ft_init_term(&term);
	ft_minishell(&term);
	return (0);
}
