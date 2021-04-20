/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:09:41 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/20 17:27:05 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_add_new_char(char **str, char *newchar, int buff_size)
{
	char *tmp;

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

int	ft_write_char(char *character, char **line, int *fsize, char **prev_line)
{
	int		ret;
	int		len;

	ret = ft_strlen(character);
	len = ft_strlen(*line);
	if (!ft_strncmp(character, "\e[B", ret))
		ft_put_history_down(&len, line, fsize, prev_line);
	else if (!ft_strncmp(character, "\e[A", ret))
		ft_put_history_up(&len, line, fsize, prev_line);
	else if (!ft_strncmp(character, "\x7f", ret))
		ft_del_char(&len, line);
	else if (!ft_strncmp(character, "\e[D", ret))
		return (len);
	else if (!ft_strncmp(character, "\e[C", ret))
		return (len);
	else if (!ft_strncmp(character, "\n", ret))
		return (len);
	else
	{
		write(1, character, ret);
		len += ret;
		len = ft_add_new_char(line, character, len);
	}
	return (len);
}

int	ft_read(char **line)
{
	int		len;
	int		ret;
	char	*character;
	int		fsize;
	char	*saved_line;

	len = 0;
	fsize = ft_flines_counter(g_var.path_hist);
	character = (char *)ft_calloc(BUFF_SIZE, sizeof(char));
	*line = (char *)ft_calloc(1, sizeof(char));
	saved_line = NULL;
	ft_check_errno(); // Не все стандарты меняют ерно на маллок, возможн просто exit(1)
	line[0][0] = '\0';
	tputs(save_cursor, 1, ft_putchar);
	while (1)
	{
		ret = read(STDIN_FILENO, character, BUFF_SIZE);
		character[ret] = '\0';
		ft_check_errno();
		len = ft_write_char(character, line, &fsize, &saved_line);
		if (!ft_strncmp(character, "\n", ret))
			break;
	}
	write(1, "\n", 1);
	free(saved_line);
	free(character);
	return (len);
}

void	ft_minishell(void)
{
	char	*line;

	line = NULL;
	while (1)
	{
		write(STDOUT_FILENO, "minishell$ ", 11);
		ft_read(&line);
		ft_parse(line);
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
	ft_global_init();
	ft_minishell();
	return (0);
}
