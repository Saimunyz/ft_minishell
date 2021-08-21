/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:09:41 by swagstaf          #+#    #+#             */
/*   Updated: 2021/08/21 14:14:17 by swagstaf         ###   ########.fr       */
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
	else if (*character == '\n' || *character == '\4' || *character == '\t' || *character == '\034') // сделать функция запрещенных символов
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
	ft_change_term_mode(1);
	ft_init_read(&hist, line, &character, home);
	tputs(save_cursor, 1, ft_putchar);
	while (*character != '\n')
	{
		ret = read(STDIN_FILENO, character, BUFF_SIZE);
		character[ret] = '\0';
		ft_check_errno();
		if (ft_check_sigint(line, character))
			break ;
		len = ft_write_char(character, line, &hist);
		ft_check_eof(line, character, &hist);
	}
	write(1, "\n", 1);
	ft_lstclear(&hist.start, free);
	free(character);
	ft_change_term_mode(0);
	return (len);
}

void	ft_minishell(t_memory *mem)
{
	char	*line;
	char	*home;

	line = NULL;
	home = getenv("HOME");
	g_error = 0;
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, ft_sigquit_handler);
	while (1)
	{
		write(STDOUT_FILENO, "minishell$ ", 11);
		ft_read(&line, home);
		ft_parse(line, home, mem);
		ft_check_errno();
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_memory	mem;

	mem.envp = envp; //Сергей 20.08.21
	errno = 0;
	(void)argc;
	(void)argv;
	if (ft_get_term_info() != 0)
		exit(1);
	ft_init_mem(&mem, envp);
	ft_minishell(&mem);
//	ft_lstclear(&mem.env, free); //Сергей мы же сюда никогда не попадаем
	return (0);
}
