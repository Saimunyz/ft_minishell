/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:10:37 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/21 15:00:38 by swagstaf         ###   ########.fr       */
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

typedef struct s_global_var
{
	char	*env_home;
	char	*path_hist;
}			t_global_var;

t_global_var	g_var;

void	ft_global_init(void);
void	ft_clear_global(void);
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
void	ft_init_read(t_list **hist, t_list	**start, char **line, char **lettr);
void	ft_write_history(char *command);
t_list	*ft_read_history(void);
void	ft_put_history_down(int *len, char **line, t_list **hist, t_list *strt);
void	ft_put_history_up(int *len, char **line, t_list **hist);

#endif
