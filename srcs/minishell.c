/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:09:41 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/16 15:55:08 by swagstaf         ###   ########.fr       */
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

int	ft_write_char(char *character, char **line)
{
	int		ret;
	int		len;

	ret = ft_strlen(character);
	len = ft_strlen(*line);
	if (!ft_strncmp(character, "\e[B", ret))
		printf("next\n");
	else if (!ft_strncmp(character, "\e[A", ret))
		printf("previous\n");
	else if (!ft_strncmp(character, "\x7f", ret))
		ft_term_action("dc");
	else if (ft_strncmp(character, "\n", ret))
	{
		len += ret;
		len = ft_add_new_char(line, character, len);
	}
	write(1, character, ret);
	return (len);
}

int	ft_read(char **line)
{
	int		len;
	int		ret;
	char	*character;

	len = 0;
	character = (char *)ft_calloc(BUFF_SIZE, sizeof(char));
	*line = (char *)ft_calloc(1, sizeof(char));
	ft_check_errno(); // Не все стандарты меняют ерно на маллок, возможн просто exit(1)
	line[0][0] = '\0';
	while (1)
	{
		ret = read(STDIN_FILENO, character, BUFF_SIZE);
		character[ret] = '\0';
		ft_check_errno();
		len = ft_write_char(character, line);
		if (!ft_strncmp(character, "\n", ret))
			break;
	}
	free(character);
	return (len);
}

void	ft_minishell(t_term *term)
{
	char	*line;
	int		len;

	line = NULL;
	len = 0;
	if (ft_get_term_info() != 0)
		exit(1);
	while (1)
	{
		write(STDOUT_FILENO, "minishell$ ", 11);
		len = ft_read(&line);
		ft_parse(line, len);
		ft_check_errno();
		free(line);
	}
	ft_change_term_mode(term);
}

int	main(void)
{
	t_term	term;

	errno = 0;
	ft_init_term(&term);
	ft_minishell(&term);
	return (0);
}
