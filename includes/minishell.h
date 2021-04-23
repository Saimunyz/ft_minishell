/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:10:37 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/23 16:42:38 by swagstaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "stdio.h"
# include "term.h"
# include "termios.h"
# include "libft.h"
# include "errno.h"
# include "string.h"
# include "fcntl.h"

# define BUFF_SIZE 10

# define KEY_UP 0001
# define KEY_DOWN 0010
# define GET_DATA_ERR 1

typedef struct s_hist
{
	t_list *hist;
	t_list *start;
}			t_hist;

int		g_error;

void	ft_global_init(void);
void	ft_clear_global(void);
void	ft_check_errno(void);
void	ft_change_term_mode(int change);
int		ft_get_term_info(void);
int		ft_parse(char *line, char *home);
void	ft_pwd(void);
void	ft_del_char(int *len, char **line);
void	ft_del_line(int *len, char **line);
void	ft_echo(char *str, int flag);
void	ft_cd(char *path);
void	ft_exit(void);
void	ft_init_read(t_hist *hist, char **line, char **lettr, char *home);
void	ft_write_history(char *command, char *home);
t_list	*ft_read_history(char *home);
void	ft_put_history_down(int *len, char **line, t_hist *hist);
void	ft_put_history_up(int *len, char **line, t_hist *hist);
int		ft_check_sigint(char **line, char *character);
void	ft_check_eof(char **line, char *character, t_hist *hist);

#endif
