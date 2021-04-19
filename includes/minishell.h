/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:10:37 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/20 02:28:34 by swagstaf         ###   ########.fr       */
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

extern char	*g_path;

# define BUFF_SIZE 10

# define KEY_UP 0001
# define KEY_DOWN 0010
# define GET_DATA_ERR 1

typedef struct s_hist
{
	t_list	*hist;
	t_list	*start;
}				t_hist;


void	ft_check_errno(void);
void	ft_change_term_mode(int change);
int		ft_get_term_info(void);
int		ft_parse(char *line);
void	ft_pwd(void);
void	ft_del_char(int *len, char **line);
void	ft_del_line(int *len, char **line);
void	ft_echo(char *str, int flag);
void	ft_cd(char *path);
void	ft_exit(void);
void	ft_write_history(char *command);
t_list	*ft_read_history(void);
void	ft_put_history(int *len, char **line, int keycode, t_hist hist);

#endif
