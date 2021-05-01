/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:10:37 by swagstaf          #+#    #+#             */
/*   Updated: 2021/05/02 02:18:23 by swagstaf         ###   ########.fr       */
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
# include "sys/stat.h"
# include "sys/wait.h"

# define BUFF_SIZE 10
# define GET_DATA_ERR 1
# define COMMAND_ERR 2

typedef struct s_hist
{
	t_list	*hist;
	t_list	*start;
}			t_hist;

typedef struct s_env
{
	t_list	*shlvl;
	t_list	*pwd;
	t_list	*oldpwd;
	t_list	*env;
}			t_env;

int		g_error;

void	ft_check_errno(void);
void	ft_change_term_mode(int change);
int		ft_get_term_info(void);
void	ft_parse(char *line, char *home, t_env *env);
void	ft_pwd(void);
void	ft_del_char(int *len, char **line);
void	ft_del_line(int *len, char **line);
void	ft_echo(char *str, int flag);
void	ft_cd(char *path, t_env *env);
void	ft_exit(void);
void	ft_commands(char **splt);
void	ft_init_read(t_hist *hist, char **line, char **lettr, char *home);
void	ft_write_history(char *command, char *home);
t_list	*ft_read_history(char *home);
void	ft_put_history_down(int *len, char **line, t_hist *hist);
void	ft_put_history_up(int *len, char **line, t_hist *hist);
int		ft_check_sigint(char **line, char *character);
void	ft_check_eof(char **line, char *character, t_hist *hist);
void	ft_print_bash_err(char *line);
void	ft_init_env(t_env *env, char **envp);
void	ft_env(t_env env);

#endif
