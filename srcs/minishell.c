/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:09:41 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/15 16:52:24 by swagstaf         ###   ########.fr       */
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

static int	ft_extend_buff(char *str, int buff_size)
{
	if (buff_size > 2147483647)
		buff_size = 2147483647;
	str = ft_realloc(str, buff_size);
	ft_check_errno();
	return (buff_size);
}

void	ft_write_char(char *character, char *line, int *left_right, int *len)
{
	int	ret;

	ret = ft_strlen(character);
	if (!ft_strncmp(character, "\e[B", ret))
		printf("next\n");
	else if (!ft_strncmp(character, "\e[A", ret))
		printf("previous\n");
	else if (!ft_strncmp(character, "\e[C", ret))
	{
		if (*left_right < *len)
		{
			write(1, character, ret);
			left_right++;
		}
	}
	else if (!ft_strncmp(character, "\e[D", ret))
	{
		if (*left_right > 12)
		{
			write(1, character, ret);
			left_right--;
		}
	}
	else
	{
		write(1, character, ret);
		*len += ret;
		*len = ft_extend_buff(line, *len);
		ft_strlcat(line, character, *len);
	}
}

int	ft_read(char *line)
{
	int		buff_size;
	int		len;
	int		ret;
	char	*character;
	int		left_right;

	len = 0;
	left_right = 12;
	buff_size = BUFF_SIZE;
	character = (char *)malloc(sizeof(char) * buff_size);
	line = (char *)malloc(sizeof(char) * 1);
	line[0] = '\0';
	ft_check_errno(); // Не все стандарты меняют ерно на маллок, возможн просто exit(1)
	while (1)
	{
		ret = read(STDIN_FILENO, character, buff_size);
		character[ret] = '\0';
		ft_check_errno();
		ft_write_char(character, line, &left_right, &len);
		if (ret > buff_size)
			buff_size = ft_extend_buff(line, buff_size + BUFF_SIZE);
		if (!ft_strncmp(character, "\n", ret))
			break;
	}
	free(character);
	return (len);
}

void	ft_minishell(t_term *term)
{
	char	*line;

	line = NULL;
	if (ft_get_term_info() != 0)
		exit(1);
	while (1)
	{
		write(STDOUT_FILENO, "minishell$ ", 11);
		ft_read(line);
		//ft_parse(line, ft_strlen(line));
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
