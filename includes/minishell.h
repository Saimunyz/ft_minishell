/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:10:37 by swagstaf          #+#    #+#             */
/*   Updated: 2021/04/20 17:26:17 by swagstaf         ###   ########.fr       */
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

typedef struct g_global_var
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
int		ft_flines_counter(char *filepath);
void	ft_write_history(char *command);
char	*ft_read_history(int line_num);
void	ft_put_history_down(int *len, char **line, int *fsize, char **saved);
void	ft_put_history_up(int *len, char **line, int *fsize, char **saved);

#endif
