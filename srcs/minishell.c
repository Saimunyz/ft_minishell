/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:09:41 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/23 17:01:29 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_add_new_char(char **str, char *newchar, int buff_size)
{
	char	*tmp;

	tmp = NULL;
	if (buff_size > 2147483647)
		buff_size = 2147483647;
	*str = ft_realloc(*str, buff_size);
	ft_check_errno();
	tmp = ft_strjoin(*str, newchar);
	free(*str);
	*str = tmp;
	return (buff_size);
}

int	ft_write_char(char *character, char **line, t_hist *hist)
{
	int		ret;
	int		len;

	ret = ft_strlen(character);
	len = ft_strlen(*line);
	if (!ft_strncmp(character, "\e[B", ret))
		ft_put_history_down(&len, line, hist);
	else if (!ft_strncmp(character, "\e[A", ret))
		ft_put_history_up(&len, line, hist);
	else if (!ft_strncmp(character, "\x7f", ret))
		ft_del_char(&len, line);
	else if (!ft_strncmp(character, "\e[D", ret))
		return (len);
	else if (!ft_strncmp(character, "\e[C", ret))
		return (len);
	else if (*character == '\n' || *character == '\4')
		return (len);
	else
	{
		write(1, character, ret);
		len += ret;
		len = ft_add_new_char(line, character, len);
	}
	return (len);
}

int	ft_read(char **line, char *home)
{
	int		len;
	int		ret;
	char	*character;
	t_hist	hist;

	len = 0;
	ft_init_read(&hist, line, &character, home);
	tputs(save_cursor, 1, ft_putchar);
	while (1)
	{
		ret = read(STDIN_FILENO, character, BUFF_SIZE);
		character[ret] = '\0';
		ft_check_errno();
		if (ft_check_sigint(line, character))
			break ;
		len = ft_write_char(character, line, &hist);
		ft_check_eof(line, character, &hist);
		if (!ft_strncmp(character, "\n", ret))
			break ;
		g_error = 127; // поправить
	}
	write(1, "\n", 1);
	ft_lstclear(&hist.start, free);
	free(character);
	return (len);
}

void	ft_minishell(void)
{
	char	*line;
	int		len;
	char	*home;

	line = NULL;
	len = 0;
	home = getenv("HOME");
	g_error = 0;
	while (1)
	{
		write(STDOUT_FILENO, "minishell$ ", 11);
		len = ft_read(&line, home);
		if (*line == '\4')
			break ;
		ft_parse(line, home);
		ft_check_errno();
		free(line);
	}
}

int	main(void)
{
	errno = 0;
	if (ft_get_term_info() != 0)
		exit(1);
	ft_change_term_mode(1);
	ft_minishell();
	ft_change_term_mode(0);
	return (0);
}
